cmake_minimum_required(VERSION 2.8)
project( ocr_preprocessing_nib )
find_package( OpenCV REQUIRED )
add_executable( ocr_preprocessing_nib main.cpp )
target_link_libraries( ocr_preprocessing_nib ${OpenCV_LIBS} )

