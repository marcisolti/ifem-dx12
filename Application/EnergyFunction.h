#pragma once

#include <Eigen/Dense>
#include <algorithm>

typedef Eigen::Matrix<double, 3, 3>  Mat3;
typedef Eigen::Matrix<double, 9, 9>  Mat9;
typedef Eigen::Matrix<double, 12, 12> Mat12;
typedef Eigen::Matrix<double, 9, 12> Mat9x12;
typedef Eigen::Matrix<double, 12, 9> Mat12x9;

typedef Eigen::Matrix<double, 3, 1>  Vec3;
typedef Eigen::Matrix<double, 9, 1>  Vec9;
typedef Eigen::Matrix<double, 12, 1>  Vec12;

inline Vec9 Flatten(const Mat3& mat);

class EnergyFunction
{
protected:
	double E, nu, lambda, mu;
	Mat3 F;
public:
	EnergyFunction(double E = 1.0e6, double nu = 0.4)
		: E{ E }, nu{ nu }
	{
		lambda = nu * E / ((1.0 + nu) * (1.0 - 2.0 * nu)); // from vega fem homogeneousNeoHookeanIsotropicMaterial.cpp
		mu = E / (2.0 * (1.0 + nu));
	}

	virtual Mat3 GetPK1(const Mat3& F) = 0;

	virtual Mat9 GetJacobian() = 0;
};

class Dirichlet : public EnergyFunction
{
public:
	Dirichlet(double E = 1.0e6, double nu = 0.4) : EnergyFunction{ E, nu } {};

	virtual Mat3 GetPK1(const Mat3& F) override
	{
		return 2.0 * F;
	}

	virtual Mat9 GetJacobian() override
	{
		return 2.0 * Mat9::Identity();
	}
};

class StVK : public EnergyFunction
{
public:
	StVK(double E = 1.0e6, double nu = 0.4) : EnergyFunction{ E, nu } {};

	virtual Mat3 GetPK1(const Mat3& F) override
	{
		this->F = F;

		Mat3 E = 0.5 * (F.transpose() * F - Mat3::Identity());
		Mat3 P = mu * F * E + lambda * E.trace() * F;

		return P;
	}

	virtual Mat9 GetJacobian() override { return Mat9{}; };
};

class NeoHookean : public EnergyFunction
{

	Vec3 f0, f1, f2;
	Mat3 dJdF;
	double J;

public:
	NeoHookean(double E = 1.0e6, double nu = 0.4) : EnergyFunction{ E, nu } {};

	virtual Mat3 GetPK1(const Mat3& F) override
	{
		this->F = F;
		J = F.determinant();

		f0 << F(0, 0), F(0, 1), F(0, 2);
		f1 << F(1, 0), F(1, 1), F(1, 2);
		f2 << F(2, 0), F(2, 1), F(2, 2);

		Vec3 dJdF_0 = f1.cross(f2);
		Vec3 dJdF_1 = f2.cross(f0);
		Vec3 dJdF_2 = f0.cross(f1);

		dJdF <<
			dJdF_0(0), dJdF_1(0), dJdF_2(0),
			dJdF_0(1), dJdF_1(1), dJdF_2(1),
			dJdF_0(2), dJdF_1(2), dJdF_2(2);

		Mat3 P = mu * (F - 1.0 / J * dJdF) + ((lambda * std::log(J)) / J) * dJdF;

		return P;
	}
	virtual Mat9 GetJacobian() override
	{
		Vec9 gJ = Flatten(dJdF);

		Mat9 gJgJT = gJ * gJ.transpose();

		Mat3 f0Hat, f1Hat, f2Hat;
		f0Hat <<
			0.0, -f0(2), f0(1),
			f0(2), 0.0, -f0(0),
			-f0(1), f0(0), 0.0;

		f1Hat <<
			0.0, -f1(2), f1(1),
			f1(2), 0.0, -f1(0),
			-f1(1), f1(0), 0.0;

		f2Hat <<
			0.0, -f2(2), f2(1),
			f2(2), 0.0, -f2(0),
			-f2(1), f2(0), 0.0;

		Mat9 HJ;
		HJ <<
			0.0, 0.0, 0.0, -f2Hat(0, 0), -f2Hat(0, 1), -f2Hat(0, 2), f1Hat(0, 0), f1Hat(0, 1), f1Hat(0, 2),
			0.0, 0.0, 0.0, -f2Hat(1, 0), -f2Hat(1, 1), -f2Hat(1, 2), f1Hat(1, 0), f1Hat(1, 1), f1Hat(1, 2),
			0.0, 0.0, 0.0, -f2Hat(2, 0), -f2Hat(2, 1), -f2Hat(2, 2), f1Hat(2, 0), f1Hat(2, 1), f1Hat(2, 2),

			f2Hat(0, 0), f2Hat(0, 1), f2Hat(0, 2), 0.0, 0.0, 0.0, -f0Hat(0, 0), -f0Hat(0, 1), -f0Hat(0, 2),
			f2Hat(1, 0), f2Hat(1, 1), f2Hat(1, 2), 0.0, 0.0, 0.0, -f0Hat(1, 0), -f0Hat(1, 1), -f0Hat(1, 2),
			f2Hat(2, 0), f2Hat(2, 1), f2Hat(2, 2), 0.0, 0.0, 0.0, -f0Hat(2, 0), -f0Hat(2, 1), -f0Hat(2, 2),

			-f1Hat(0, 0), -f1Hat(0, 1), -f1Hat(0, 2), f0Hat(0, 0), f0Hat(0, 1), f0Hat(0, 2), 0.0, 0.0, 0.0,
			-f1Hat(1, 0), -f1Hat(1, 1), -f1Hat(1, 2), f0Hat(1, 0), f0Hat(1, 1), f0Hat(1, 2), 0.0, 0.0, 0.0,
			-f1Hat(2, 0), -f1Hat(2, 1), -f1Hat(2, 2), f0Hat(2, 0), f0Hat(2, 1), f0Hat(2, 2), 0.0, 0.0, 0.0;

		return
			mu * Mat9::Identity() +
			((mu + lambda * (1.0 - std::log(J))) / (J * J)) * gJgJT +
			((lambda * std::log(J) - mu) / J) * HJ;

	}
};

class StableNeoHookean : public EnergyFunction
{

	Vec3 f0, f1, f2;
	Mat3 dJdF;
	double J;

public:
	StableNeoHookean(double E = 1.0e6, double nu = 0.4) : EnergyFunction{ E, nu } {};

	virtual Mat3 GetPK1(const Mat3& F) override
	{
		this->F = F;
		J = F.determinant();

		f0 << F(0, 0), F(0, 1), F(0, 2);
		f1 << F(1, 0), F(1, 1), F(1, 2);
		f2 << F(2, 0), F(2, 1), F(2, 2);

		Vec3 dJdF_0 = f1.cross(f2);
		Vec3 dJdF_1 = f2.cross(f0);
		Vec3 dJdF_2 = f0.cross(f1);

		dJdF <<
			dJdF_0(0), dJdF_1(0), dJdF_2(0),
			dJdF_0(1), dJdF_1(1), dJdF_2(1),
			dJdF_0(2), dJdF_1(2), dJdF_2(2);

		Mat3 P = (mu / 2) * 2.0 * F + (lambda * (J - 1.0) - mu) * dJdF;
		//Mat3 P = mu * (F - 1.0 / J * dJdF) + ((lambda * std::log(J)) / J) * dJdF;

		return P;
	}
	virtual Mat9 GetJacobian() override
	{

		Vec9 gJ = Flatten(dJdF);
		Mat9 gJgJT = gJ * gJ.transpose();

		Mat9 H2 = 2.0 * Mat9::Identity();

		Mat3 f0Hat, f1Hat, f2Hat;
		f0Hat <<
			0.0, -f0(2), f0(1),
			f0(2), 0.0, -f0(0),
			-f0(1), f0(0), 0.0;

		f1Hat <<
			0.0, -f1(2), f1(1),
			f1(2), 0.0, -f1(0),
			-f1(1), f1(0), 0.0;

		f2Hat <<
			0.0, -f2(2), f2(1),
			f2(2), 0.0, -f2(0),
			-f2(1), f2(0), 0.0;

		Mat9 HJ;
		HJ <<
			0.0, 0.0, 0.0, -f2Hat(0, 0), -f2Hat(0, 1), -f2Hat(0, 2), f1Hat(0, 0), f1Hat(0, 1), f1Hat(0, 2),
			0.0, 0.0, 0.0, -f2Hat(1, 0), -f2Hat(1, 1), -f2Hat(1, 2), f1Hat(1, 0), f1Hat(1, 1), f1Hat(1, 2),
			0.0, 0.0, 0.0, -f2Hat(2, 0), -f2Hat(2, 1), -f2Hat(2, 2), f1Hat(2, 0), f1Hat(2, 1), f1Hat(2, 2),

			f2Hat(0, 0), f2Hat(0, 1), f2Hat(0, 2), 0.0, 0.0, 0.0, -f0Hat(0, 0), -f0Hat(0, 1), -f0Hat(0, 2),
			f2Hat(1, 0), f2Hat(1, 1), f2Hat(1, 2), 0.0, 0.0, 0.0, -f0Hat(1, 0), -f0Hat(1, 1), -f0Hat(1, 2),
			f2Hat(2, 0), f2Hat(2, 1), f2Hat(2, 2), 0.0, 0.0, 0.0, -f0Hat(2, 0), -f0Hat(2, 1), -f0Hat(2, 2),

			-f1Hat(0, 0), -f1Hat(0, 1), -f1Hat(0, 2), f0Hat(0, 0), f0Hat(0, 1), f0Hat(0, 2), 0.0, 0.0, 0.0,
			-f1Hat(1, 0), -f1Hat(1, 1), -f1Hat(1, 2), f0Hat(1, 0), f0Hat(1, 1), f0Hat(1, 2), 0.0, 0.0, 0.0,
			-f1Hat(2, 0), -f1Hat(2, 1), -f1Hat(2, 2), f0Hat(2, 0), f0Hat(2, 1), f0Hat(2, 2), 0.0, 0.0, 0.0;

		return
			(mu / 2) * H2 +
			lambda * gJgJT +
			(lambda * (J - 1) - mu) * HJ;

	}
};

class ARAP : public EnergyFunction
{

	Mat3 U, V, S, R;
	Vec3 Sigma;

public:
	ARAP(double E = 1.0e6, double nu = 0.4) : EnergyFunction{ E, nu } {};

	virtual Mat3 GetPK1(const Mat3& F) override
	{
		this->F = F;
		// P = mu(F - R);
		using namespace Eigen;
		Eigen::JacobiSVD<Mat3> SVD(F, ComputeFullU | ComputeFullV);
		Sigma = SVD.singularValues();
		U = SVD.matrixU();
		V = SVD.matrixV();

		R = U * V.transpose();
		return mu * (F - R);
	}
	virtual Mat9 GetJacobian() override
	{
		double sq2inv = 1.0 / std::sqrt(2.0);

		double eigenLambda[3];

		eigenLambda[0] = 2.0 / (Sigma(0) + Sigma(1));
		eigenLambda[1] = 2.0 / (Sigma(1) + Sigma(2));
		eigenLambda[2] = 2.0 / (Sigma(0) + Sigma(2));

		if (Sigma(0) + Sigma(1) < 2.0)
			eigenLambda[0] = 1.0;

		if (Sigma(1) + Sigma(2) < 2.0)
			eigenLambda[1] = 1.0;

		if (Sigma(0) + Sigma(2) < 2.0)
			eigenLambda[2] = 1.0;

		Vec9 Q[3];

		Mat3 T1 = Mat3::Zero();
		T1(0, 1) = -1.0;
		T1(1, 0) = 1.0;
		Q[0] = Flatten(sq2inv * U * T1 * V.transpose());

		Mat3 T2 = Mat3::Zero();
		T2(1, 2) = 1.0;
		T2(2, 1) = -1.0;
		Q[1] = Flatten(sq2inv * U * T2 * V.transpose());

		Mat3 T3 = Mat3::Zero();
		T3(0, 2) = 1.0;
		T3(2, 0) = -1.0;
		Q[2] = Flatten(sq2inv * U * T3 * V.transpose());

		Mat9 H1 = Mat9::Identity();

		for (int i = 0; i < 3; ++i)
			H1 -= eigenLambda[i] * Q[i] * Q[i].transpose();

		return 2.0 * H1;
	}
};


inline Vec9 Flatten(const Mat3& mat)
{
	Vec9 vec;
	int index = 0;
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 3; x++, index++)
			vec(index) = mat(x, y);
	return vec;
}
