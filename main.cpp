#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    // Create and open a text file
    ofstream MyFile("repeated_logs.txt");

    // Write to the file


    for (int i = 0; i < 580 ;i++) {
        MyFile << "Oct 9 13:38:47 998.94.195.38:4160 Failed password for admin\n";
        MyFile << "Jul 2 23:57:14 998.52.253.8:5544 Failed password for illegal user guest\n";
        MyFile << "Jul 12 16:40:59 997.89.828.75:6256 Failed password for illegal user test\n";
        MyFile << "Jun 10 02:43:47 997.21.797.48:5757 Failed password for illegal user test\n";
        MyFile << "Oct 29 15:56:19 996.59.290.91:5542 Failed password for illegal user guest\n";
        MyFile << "Sep 20 06:32:22 993.75.119.62:5474 Failed password for illegal user guest\n";
        MyFile << "Jul 9 18:02:24 990.65.351.90:5317 Failed password for root\n";
        MyFile << "Jul 27 12:05:51 987.66.495.13:6007 Failed password for root\n";
        MyFile << "Jun 16 06:03:20 985.87.922.60:6844 Failed password for illegal user guest\n";
        MyFile << "Sep 27 20:38:33 981.98.221.70:5274 Failed password for illegal user guest\n";
        MyFile << "Aug 19 08:30:01 980.6.698.55:4466 Failed password for illegal user test\n";
        MyFile << "Oct 14 03:22:14 976.38.883.41:5939 Failed password for admin\n";
        MyFile << "Jun 30 09:05:38 973.86.539.98:4152 Failed password for root\n";
        MyFile << "Aug 13 20:48:12 970.9.590.94:5573 Failed password for illegal user test\n";
        MyFile << "Oct 8 19:45:07 967.25.980.75:5728 Failed password for illegal user test\n";
        MyFile << "Aug 4 17:15:33 963.84.637.9:4986 Failed password for illegal user guest\n";
        MyFile << "Oct 24 10:27:07 957.55.287.37:4357 Illegal user\n";
        MyFile << "Jun 4 10:15:49 953.97.185.63:6702 Failed password for illegal user guest\n";
        MyFile << "Aug 23 19:44:38 951.11.545.45:4881 Illegal user\n";
        MyFile << "Aug 6 18:15:52 946.32.567.25:4716 Illegal user\n";
        MyFile << "Aug 4 17:49:38 942.33.78.74:6788 Failed password for illegal user guest\n";
        MyFile << "Oct 14 03:55:45 938.7.792.40:5976 Failed password for illegal user guest\n";
        MyFile << "Jul 9 17:11:56 933.57.43.35:6005 Failed password for illegal user test\n";
        MyFile << "Oct 7 08:17:02 929.71.114.74:6442 Failed password for root\n";
        MyFile << "Sep 15 02:28:33 929.33.246.52:6786 Illegal user\n";
        MyFile << "Jul 12 12:45:58 923.72.167.48:4413 Failed password for root\n";
        MyFile << "Oct 21 14:41:48 920.90.415.28:6415 Failed password for illegal user guest\n";
        MyFile << "Jun 20 23:54:33 918.89.578.44:4178 Failed password for root\n";
        MyFile << "Sep 28 20:29:34 916.7.890.34:4016 Failed password for admin\n";
    }

    // Close the file
    MyFile.close();

    ofstream MyFile2("just_one_log.txt");
    for (int i = 0; i < 16807 ;i++) {
        MyFile2 << "Sep 28 20:29:34 916.7.890.34:4016 Failed password for admin\n";
    }

    MyFile2.close();

}