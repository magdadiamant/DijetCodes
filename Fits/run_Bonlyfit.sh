#!/bin/bash

# ./run_Bonlyfit.sh 1 10 1

bin_No=$1
bin_No_final=$2
#bin_No_file=$3

	

	while (( $bin_No < $bin_No_final +1 ))
	do
		python python/BinnedFit_4J.py -c config/fourjet_alpha"$bin_No".config -l 137000 inputs/13bins/HISTOS_4J_Alldata_SR_alphabin"$bin_No".root -b PFDijet2017_4J_alphabin"$bin_No" -d output_alphabinning/13bins/3dijetfunction/BonlyFit/ --fit-spectrum
		#python python/BinnedFit_4J.py -c config/moddijet_config/fourjet_alpha"$bin_No".config -l 137000 inputs/13bins/HISTOS_4J_Alldata_SR_alphabin"$bin_No".root -b PFDijet2017_4J_alphabin"$bin_No" -d output_alphabinning/13bins_moddijet/3dijetfunction/BonlyFit/ --fit-spectrum
		#python python/BinnedFit_4J.py -c config/fourjet_alpha"$bin_No".config -l 137000 inputs/48bins/HISTOS_4J_Alldata_SR_alphabin"$bin_No_file".root -b PFDijet2017_4J_alphabin"$bin_No" -d output_alphabinning/48bins/3dijetfunction/BonlyFit/ --fit-spectrum
		bin_No=$(( bin_No+1 ))
		#bin_No_file=$(( bin_No_file+1 ))
	done



