# %%

from decimal import *
import matplotlib.pyplot as plt
import numpy as np

# %%

data1 = np.loadtxt('C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\3_dataset_1.csv', dtype=np.float64,
                   delimiter=',', skiprows=1)
data1Xs = data1[:, 0].tolist()
data1Ys = data1[:, 1].tolist()
#
data2 = np.loadtxt('C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\3_dataset_2.csv', dtype=np.float64,
                   delimiter=',', skiprows=1)
data2Xs = data2[:, 0].tolist()
data2Ys = data2[:, 1].tolist()
#
data1NewtPred = np.loadtxt('C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Newt_Pred_Points_1.csv',
                           dtype=np.float64, delimiter=',', skiprows=1)
data1NewtPredXs = data1NewtPred[:, 0].tolist()
data1NewtPredYs = data1NewtPred[:, 2].tolist()
#
data1NewtTestPred = np.loadtxt(
    'C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Newt_Test_Pred_Points_1.csv', dtype=np.float64,
    delimiter=',', skiprows=1)
data1NewtTestPredXs = data1NewtTestPred[:, 0].tolist()
data1NewtTestPredYs = data1NewtTestPred[:, 2].tolist()
#
data2NewtPred = np.loadtxt('C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Newt_Pred_Points_2.csv',
                           dtype=np.float64, delimiter=',', skiprows=1)
data2NewtPredXs = data2NewtPred[:, 0].tolist()
data2NewtPredYs = data2NewtPred[:, 2].tolist()
#
data2NewtTestPred = np.loadtxt(
    'C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Newt_Test_Pred_Points_2.csv', dtype=np.float64,
    delimiter=',', skiprows=1)
data2NewtTestPredXs = data2NewtTestPred[:, 0].tolist()
data2NewtTestPredYs = data2NewtTestPred[:, 2].tolist()
#
data1CubePred = np.loadtxt('C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Cube_Pred_Points_1.csv',
                           dtype=np.float64, delimiter=',', skiprows=1)
data1CubePredXs = data1CubePred[:, 0].tolist()
data1CubePredYs = data1CubePred[:, 2].tolist()
#
data1CubeTestPred = np.loadtxt(
    'C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Cube_Test_Pred_Points_1.csv', dtype=np.float64,
    delimiter=',', skiprows=1)
data1CubeTestPredXs = data1CubeTestPred[:, 0].tolist()
data1CubeTestPredYs = data1CubeTestPred[:, 2].tolist()
#
data2CubePred = np.loadtxt('C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Cube_Pred_Points_2.csv',
                           dtype=np.float64, delimiter=',', skiprows=1)
data2CubePredXs = data2CubePred[:, 0].tolist()
data2CubePredYs = data2CubePred[:, 2].tolist()
#
data2CubeTestPred = np.loadtxt(
    'C:\\Users\\Amr\CLionProjects\\CourseWorkOne\\datasets\\part_3\\Cube_Test_Pred_Points_2.csv', dtype=np.float64,
    delimiter=',', skiprows=1)
data2CubeTestPredXs = data2CubeTestPred[:, 0].tolist()
data2CubeTestPredYs = data2CubeTestPred[:, 2].tolist()

# %%

plt.figure(dpi=130)
plt.plot(data1Xs, data1Ys, label='Original ', linewidth=1)
plt.plot(data1NewtTestPredXs, data1NewtTestPredYs, label='Newton', linewidth=1)
plt.xlabel('X - Axis')
plt.ylabel('Y - Axis')
plt.title('Data 1')
plt.legend()
plt.show()

# %%

plt.figure(dpi=130)
plt.plot(data1Xs, data1Ys, label='Original ', linewidth=1)
plt.plot(data1CubeTestPredXs, data1CubeTestPredYs, label='Spline', linewidth=1)
plt.xlabel('X - Axis')
plt.ylabel('Y - Axis')
plt.title('Data 1')
plt.legend()
plt.show()

# %%

plt.figure(dpi=130)
plt.plot(data2Xs, data2Ys, label='Original ', linewidth=1)
plt.plot(data2NewtTestPredXs, data2NewtTestPredYs, label='Newton', linewidth=1)
plt.xlabel('X - Axis')
plt.ylabel('Y - Axis')
plt.title('Data 2')
plt.legend()
plt.show()

# %%

plt.figure(dpi=130)
plt.plot(data2Xs, data2Ys, label='Original ', linewidth=1)
plt.plot(data2CubeTestPredXs, data2CubeTestPredYs, label='Spline', linewidth=1)
plt.xlabel('X - Axis')
plt.ylabel('Y - Axis')
plt.title('Data 2')
plt.legend()
plt.show()
