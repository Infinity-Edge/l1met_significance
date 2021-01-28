#!/bin/bash -f

#echo "Process name: $1"
#echo "Sample  name: $2"

if [[ "$1" == "" && "$2" == "" ]]; then
	prox="VBF"
	SAMP="perfNano_VBF_HToInvisible_PU200.110X_v1.root"

elif [[ "$1" != "" && "$2" != "" ]]; then
	prox="$1";
	SAMP="$2";

elif [[ "$1" != "" && "$2" == "" ]]; then
	echo "Process name: $1";
	echo "Please specify sample name";
	exit 0;

elif [[ "$1" == "" && "$2" != "" ]]; then
	echo "Sample name: $2";
	echo "Please specify process name";
	exit 0;
fi;

if [[ "$3" == "" ]]; then
	echo "No specified output directory: automatically make sig_110X";
	dir="sigs_110X";
fi;

echo "Process name: ${prox}";
echo "Sample  name: ${SAMP}";
echo "Output directory name: ${dir}"

if [ ! -d $dir ]; then
    mkdir $dir
fi
if [ ! -d $dir/$prox ]; then
    mkdir $dir/$prox
fi

cp met_signi.C met_signi_tmp.C
cp met_signi.h met_signi_tmp.h

sed "s/VBF/${prox}/g" met_signi_tmp.C > met_signi.C
sed "s/perfNano_VBF_HToInvisible_PU200.110X_v1.root/${SAMP}/g" met_signi_tmp.h > met_signi.h
root -l -b << EOF
.L met_signi.C
met_signi a
a.Loop("$dir", "$prox")
.q
EOF

cp met_signi_tmp.C met_signi.C
cp met_signi_tmp.h met_signi.h

rm met_signi_tmp.C
rm met_signi_tmp.h

