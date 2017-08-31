project( ocr_preprocessing_buba )
find_package( OpenCV REQUIRED )
add_executable( ocr_preprocessing_buba main.cpp )
target_link_libraries( ocr_preprocessing_buba ${OpenCV_LIBS} )

