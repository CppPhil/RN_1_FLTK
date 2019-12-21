#include "../include/MainWindow.h"
#include <cstdlib> // EXIT_FAILURE
#ifdef _MSC_VER
#   include <iostream> // std::cin
#   include <limits> // std::numeric_limits
#endif
#ifdef __linux__
#   include <X11/Xlib.h> // XInitThreads
#endif

int main(int argc, char *argv[]) {
#ifdef __linux__
	auto retVal = XInitThreads();
	if (retVal == 0) {
		throw std::runtime_error{ "XInitThreads failed" };
	}
#endif
    auto producerCount = rn1::getProducerCount(argc, argv);
    if (producerCount == -1) { // if no producer count could be extracted from the command line parameters; exit
#   ifdef _MSC_VER // if on MSVC keep window open
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#   endif
        return EXIT_FAILURE;
    }
    rn1::printDebug("Starting ", producerCount, " producers");

    using Dim = rn1::Dimension;
    using String = std::string;
    auto const mainWindowRatio = 0.85;
    auto const winSiz = rn1::getDesktopResolution() * mainWindowRatio;
    rn1::printDebug("mainWindowSize: ", winSiz);
    String const winTitle{ "Nachrichtenticker" };
    auto const inputPosXRatio = 0.416;
    auto const inputPosYRatio = 0.555555555555555;
    Dim const inputPos{ static_cast<Dim::value_type>(winSiz.getX() * inputPosXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * inputPosYRatio) };
    auto const inputSizXRatio = 0.13888888888888888888888888888889;
    auto const inputSizYRatio = 0.02469135802469135802469135802469;
    Dim const inputSiz{ static_cast<Dim::value_type>(winSiz.getX() * inputSizXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * inputSizYRatio) };
    String const inputTxt{ "Enter news:" };
    auto const sendButPosXRatio = 0.27777777777777777777777777777778;
    auto const sendButPosYRatio = inputPosYRatio;
    Dim const sendButPos{ static_cast<Dim::value_type>(winSiz.getX() * sendButPosXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * sendButPosYRatio) };
    auto const sendButSizXRatio = 0.05208333333333333333333333333333;
    auto const sendButSizYRatio = 0.03086419753086419753086419753086;
    Dim const sendButSiz{ static_cast<Dim::value_type>(winSiz.getX() * sendButSizXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * sendButSizYRatio) };
    String const sendButLbl{ "Add news" };
    auto const outFieldPosXRatio = 0.38194444444444444444444444444444;
    auto const outFieldPosYRatio = 0.06172839506172839506172839506173;
    Dim const outFieldPos{ static_cast<Dim::value_type>(winSiz.getX() * outFieldPosXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * outFieldPosYRatio) };
    auto const outFieldSizXRatio = sendButPosXRatio;
    auto const outFieldSizYRatio = sendButSizYRatio * 10.0;
    Dim const outFieldSiz{ static_cast<Dim::value_type>(winSiz.getX() * outFieldSizXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * outFieldSizYRatio) };
    String const outFieldLabel{ "Output" };
    String const choiceLabel{ "Choose news type" };
    auto const choicePosXRatio = 0.57291666666666666666666666666667;
    auto const choicePosYRatio = inputPosYRatio;
    Dim const choicePos{ static_cast<Dim::value_type>(winSiz.getX() * choicePosXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * choicePosYRatio) };
    auto const choiceSizXRatio = sendButSizXRatio;
    auto const choiceSizYRatio = outFieldPosYRatio;
    Dim const choiceSiz{ static_cast<Dim::value_type>(winSiz.getX() * choiceSizXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * choiceSizYRatio) };
    auto const pauseButPosXRatio = 0.65972222222222222222222222222222;
    auto const pauseButPosYRatio = inputPosYRatio;
    Dim const pauseButPos{ static_cast<Dim::value_type>(winSiz.getX() * pauseButPosXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * pauseButPosYRatio) };
    auto const pauseButSizXRatio = 0.10416666666666666666666666666667;
    auto const pauseButSizYRatio = outFieldPosYRatio;
    Dim const pauseButSiz{ static_cast<Dim::value_type>(winSiz.getX() * pauseButSizXRatio),
        static_cast<Dim::value_type>(winSiz.getY() * pauseButSizYRatio) };
    rn1::MainWindow mainWindow{ static_cast<std::size_t>(producerCount),
    	winSiz, winTitle, inputPos, inputSiz,
        inputTxt, sendButPos, sendButSiz, sendButLbl,
        outFieldPos, outFieldSiz, outFieldLabel,
        choicePos, choiceSiz, choiceLabel,
        pauseButPos, pauseButSiz };
    return rn1::MainWindow::run();
} // END of main
