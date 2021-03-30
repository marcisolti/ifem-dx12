#define basicRootSig "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )," \
					  "CBV(b0), CBV(b1),"\
					  "DescriptorTable("\
							"SRV(t0, numDescriptors=1)"\
					  "), "\
					  "StaticSampler(s0)"

#define lightRootSig "RootFlags( ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT )," \
					  "CBV(b0), CBV(b1)"
