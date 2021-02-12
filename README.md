# L1 MET significance calculator

It requires CMSSW for Phase-2 Level-1 study
Please follow basic instruction here: 
https://github.com/p2l1pfp/FastPUPPI/tree/11_1_X/NtupleProducer

Once you finish environment setup like below (This command can be changed depending on CMSSW version. Please check p2l1pfp repository),
```
cmsrel CMSSW_11_1_6
cd CMSSW_11_1_6/src
cmsenv
git cms-checkout-topic p2l1pfp:L1PF_11_1_6_X

# scripts
git clone git@github.com:p2l1pfp/FastPUPPI.git -b 11_1_X

scram b -j8
```
move to work directory and clone this repository.
```
cd FastPUPPI/NtupleProducer/python/
git clone https://github.com/Infinity-Edge/l1met_significance.git
cd l1met_significance
```



Before use this scripts, please prepare nominal L1 Phase-2 samples.

The sample should be placed in `FastPUPPI/NtupleProducer/python/`.

It requires PF/PUPPI jet and MET information.

`run_sig.sh` runs one specific process (`VBF(HtoInv)` as default)
Please follow the format below.
```
./run_sig.sh <Process name> <Sample name> <Output directory name>

If you run run_sig.sh without any option like below
./run_sig.sh
It will run for VBF sample
```
