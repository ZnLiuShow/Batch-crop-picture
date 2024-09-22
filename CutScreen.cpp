// CutScreen.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

std::vector<std::string> getfiles(std::string& path);

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        std::string path = argv[1];
		auto nt = getfiles(path);
        std::string folderPath = "./cutout"; // 指定要创建的文件夹路径

        try {
            if (std::filesystem::create_directory(folderPath)) {
                std::cout << "Folder created successfully: " << folderPath << std::endl;
            }
            else {
                std::cout << "Folder already exists or cannot be created: " << folderPath << std::endl;
            }
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << e.what() << std::endl;
        }

        for (auto&n: nt)
        {
            cv::Mat img = cv::imread(path + "\\" + n);
            cv::Mat c_img = img(cv::Rect(img.cols - 352, 0, 352, 352)).clone();
            cv::imwrite("cutout\\" + n, c_img);
        }
    }
    std::cout << "Hello World!\n";
}

std::vector<std::string> getfiles(std::string& path) {
	std::vector<std::string> t;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		auto filename = entry.path().filename();
		if (std::filesystem::is_regular_file(entry.status())) {
			t.push_back(filename.string());
			std::cout << "Found file: " << path + "\\" + filename.string() << std::endl;
		}
	}
	return t;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
