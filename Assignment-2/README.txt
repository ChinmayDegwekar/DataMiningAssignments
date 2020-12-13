Team Members :

- **Sagar Gaddam**		: 2019MCS2570
- **Saswat Pujari**		: 2019MCS2571
- **Chinmay Degwekar**	: 2019MCS2560

Explanation of files

 - 2019MCS2560.sh
	- Examines the farthest and the nearest data point from 100 query points in 1 million uniformly distributed data points.
 - bruteforce_knn.py
    - Computes the distances using L1, L2, and L8. Writes the results into data.csv
 - q1_plot.py
	- Plots the average ratio of farthest and the nearest distances versus d for the three distance measures. Reads from data.csv.
Clone instructions :
git clone https://github.com/ChinmayDegwekar/DataMiningAssignments.git

	



Question 1 Observations :
1) For dimension = 1, all three ratios are same. 
As per the definations of L1, L2 and L_infinity, they will not differ with single dimension.
Hence the ratio also turned out to be same.

2) For all other dimensions we observe the relation of L1 > L2 > L_infinity
 It follows from triangular inequality and is easily proveable

3) The ratios reduces exponentially as we increase the number of dimensions.
 As the dimensions increases, the volume of space increases so fast that the available data looks sparse.
 So same 1M points gives more information in low dimesions than in higher dimensions.
 This is also reffered as Curse of dimensionality.
 Thus we observe significant differnce in the farthest and closest points in lower dimensions.
 This difference reduces as dimensionality increases, resulting into smaller ratios.
 
4)(Additional observation)
  Instead of keeping constant 1M sample points, We experimented varying the samples  [100,1000,10000,100000,1000000]
 As the number of samples under consideration increases, the ratio values increases(highest for 1M)
