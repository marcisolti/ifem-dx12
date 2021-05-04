#pragma once

#include <Eigen/Dense>
#include <algorithm>

using Mat3		= Eigen::Matrix<double, 3, 3>;
using Mat9		= Eigen::Matrix<double, 9, 9>;
using Mat12		= Eigen::Matrix<double, 12, 12>;
using Mat9x12	= Eigen::Matrix<double, 9, 12>;
using Mat12x9	= Eigen::Matrix<double, 12, 9>;

using Vec3		= Eigen::Matrix<double, 3, 1>;
using Vec9		= Eigen::Matrix<double, 9, 1>;
using Vec12		= Eigen::Matrix<double, 12, 1>;

inline Vec9 Flatten(const Mat3& mat);

const double sqrt2Inv = 1.0 / std::sqrt(2.0);


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

	virtual Mat9 GetJacobian() override 
	{ 
		//SVD, polar decomposition
		using namespace Eigen;
		Vec3 Sigma;
		Mat3 U, V, SigMat, S;
		{

			JacobiSVD<Mat3> SVD(F, ComputeFullU | ComputeFullV);
			Sigma = SVD.singularValues();
			Mat3 U = SVD.matrixU();
			Mat3 V = SVD.matrixV();

			Mat3 L = Mat3::Identity();
			L(2, 2) = (U * V.transpose()).determinant();
		
			if (U.determinant() < 0.0 && V.determinant() > 0.0)
				U = U * L;

			if (U.determinant() > 0.0 && V.determinant() < 0.0)
				V = V * L;

			Mat3 SigMat = Mat3::Zero();
			for (int i = 0; i < 3; ++i)
				SigMat(i, i) = Sigma(i);
			
			S = V * SigMat * V.transpose();
		}

		// invariants
		double I1 = S.trace();
		double I2 = (F * F.transpose()).trace();
		double I3 = F.determinant();

		double eigenVal[9];
		// probing a 3x3 matrix to get lambda_{0,1,2}
		{

			Mat3 A;
			for (int i = 0; i < 3; ++i) {
				for (int j = 0; j < 3; ++j) {
					A(i, j) = lambda * Sigma(i) * Sigma(j);
				}
			}
			for (int i = 0; i < 3; ++i) {
				A(i,i) = -mu + (lambda / 2) * (I2 - 3.0) + (lambda + 3.0 * mu) * Sigma(i) * Sigma(i);
			}

			Vector3cd lambdaMat = A.eigenvalues();
			for (int i = 0; i < 3; ++i)
				eigenVal[i] = lambdaMat(i).real();

		}

		// other eigenvals
		{
			eigenVal[3] = -mu + (lambda / 2) * (I2 - 3.0) + mu * ( Sigma(1)*Sigma(1) + Sigma(2)*Sigma(2) - Sigma(1)*Sigma(2) );
			eigenVal[4] = -mu + (lambda / 2) * (I2 - 3.0) + mu * ( Sigma(0)*Sigma(0) + Sigma(2)*Sigma(2) - Sigma(0)*Sigma(2) );
			eigenVal[5] = -mu + (lambda / 2) * (I2 - 3.0) + mu * ( Sigma(0)*Sigma(0) + Sigma(1)*Sigma(1) - Sigma(0)*Sigma(1) );
			eigenVal[6] = -mu + (lambda / 2) * (I2 - 3.0) + mu * ( Sigma(1)*Sigma(1) + Sigma(2)*Sigma(2) + Sigma(1)*Sigma(2) );
			eigenVal[7] = -mu + (lambda / 2) * (I2 - 3.0) + mu * ( Sigma(0)*Sigma(0) + Sigma(2)*Sigma(2) + Sigma(0)*Sigma(2) );
			eigenVal[8] = -mu + (lambda / 2) * (I2 - 3.0) + mu * ( Sigma(0)*Sigma(0) + Sigma(1)*Sigma(1) + Sigma(0)*Sigma(1) );
		}

		// BC projection
		for (int i = 0; i < 9; ++i) {
			if (eigenVal[i] < 0.0) {
				//eigenVal[i] = 0.0;
			}
		}

		Vec9 Q[9];
		// Q_{0,1,2}
		{
			Mat3 D[3];
			for (int i = 0; i < 3; ++i) {
				Mat3 S = Mat3::Zero();
				S(i, i) = 1.0;
				D[i] = U * S * V.transpose();
			}


			//scaling modes
			Mat3 Q123[3];
			for (int i = 0; i < 3; ++i) {
				Q123[i].setZero();
			}

			for (int s = 0; s < 3; ++s)
			{
				double z[3];
				z[0] = Sigma(0) * Sigma(2) + Sigma(1) * eigenVal[s];
				z[1] = Sigma(1) * Sigma(2) + Sigma(0) * eigenVal[s];
				z[2] = eigenVal[s] * eigenVal[s] - Sigma(2) * Sigma(2);

				for (int i = 0; i < 3; ++i) {
					Q123[s] += z[i] * D[i];
				}
			}

			for (int i = 0; i < 3; ++i) {
				Q[i] = Flatten(Q123[i]);
			}
		}

		// Q_{3...8}
		{
			Mat3 T[6];
			for (int i = 0; i < 6; ++i) {
				T[i].setZero();
			}

			T[0](0, 1) = -1.0;
			T[0](1, 0) = 1.0;

			T[1](1, 2) = 1.0;
			T[1](2, 1) = -1.0;

			T[2](0, 2) = 1.0;
			T[2](2, 0) = -1.0;

			T[3](0, 1) = 1.0;
			T[3](1, 0) = 1.0;

			T[4](1, 2) = 1.0;
			T[4](2, 1) = 1.0;

			T[5](0, 2) = 1.0;
			T[5](2, 0) = 1.0;


			for (int i = 0; i < 6; ++i) {
				Q[i + 3] = Flatten(sqrt2Inv * U * T[i] * V.transpose());
			}


		}

		Mat9 H = Mat9::Zero();
		for (int i = 0; i < 9; ++i) {
			H += eigenVal[i] * Q[i] * Q[i].transpose();
		}

		return H;
	};
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
		JacobiSVD<Mat3> SVD(F, ComputeFullU | ComputeFullV);
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
