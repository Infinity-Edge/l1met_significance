#!/bin/bash -f

echo "Run for all processes: VBF, TTbar, DY and Minbias"

if [[ "$3" == "" ]]; then
	echo "No specified output directory: automatically make sig_110X";
	dir="sigs_110X";
fi;

if [ ! -d $dir ]; then
    mkdir $dir
fi
if [ ! -d $dir/VBF ]; then
    mkdir $dir/VBF
fi
if [ ! -d $dir/DYToLL ]; then
    mkdir $dir/DYToLL
fi
if [ ! -d $dir/TTbar ]; then
    mkdir $dir/TTbar
fi
if [ ! -d $dir/Minbias ]; then
    mkdir $dir/Minbias
fi

cp met_signi.C met_signi_tmp.C
cp met_signi.h met_signi_tmp.h

root -l -b << EOF
.L met_signi.C
met_signi a
a.Loop()
.q
EOF

sed 's/VBF/TTbar/' met_signi_tmp.C > met_signi.C
sed 's/perfNano_VBF_HToInvisible_PU200.110X_v1.root/perfNano_TTbar_PU200.110X_v1.root/' met_signi_tmp.h > met_signi.h
root -l -b << EOF
.L met_signi.C
met_signi a
a.Loop()
.q
EOF

sed 's/VBF/DYToLL/' met_signi_tmp.C > met_signi.C
sed 's/perfNano_VBF_HToInvisible_PU200.110X_v1.root/perfNano_DYToLL_PU200.110X_v1.root/' met_signi_tmp.h > met_signi.h
root -l -b << EOF
.L met_signi.C
met_signi a
a.Loop()
.q
EOF

sed 's/VBF/Minbias/' met_signi_tmp.C > met_signi.C
sed 's/perfNano_VBF_HToInvisible_PU200.110X_v1.root/perfNano_SingleNeutrino_PU200.110X_v1.root/' met_signi_tmp.h > met_signi.h
root -l -b << EOF
.L met_signi.C
met_signi a
a.Loop()
.q
EOF

cp met_signi_tmp.C met_signi.C
cp met_signi_tmp.h met_signi.h

rm met_signi_tmp.C
rm met_signi_tmp.h

