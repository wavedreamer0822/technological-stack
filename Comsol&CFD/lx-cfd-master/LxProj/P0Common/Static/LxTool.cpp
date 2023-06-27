#include "LxTool.h"
#include <sstream>
#include <ctime>
#include <iomanip>
namespace LxCFD
{
    const double LxTool::OneThird = 1 / 3.0;
    const double LxTool::TwoThird = 2 / 3.0;
    double LxTool::RoundOff(double x, int bit)
    {
        std::stringstream ss;
        ss.precision(bit);
        ss << x;
        double result;
        ss >> result;
        return result;
    }
    std::string LxTool::GetCurrentTime()
    {
        time_t timep;
        std::time(&timep);
        char tmp[64];
        std::strftime(tmp, sizeof(tmp), "%Y/%m/%d %H:%M:%S", localtime(&timep));
        return tmp;
    }
}