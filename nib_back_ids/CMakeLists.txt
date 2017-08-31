project( ocr_preprocessing_nib_back )
find_package( OpenCV REQUIRED )
add_executable( ocr_preprocessing_nib_back main.cpp )
target_link_libraries( ocr_preprocessing_nib_back ${OpenCV_LIBS} )

