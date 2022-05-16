#file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)
#configure_file ("my_file1.jpg" ${CMAKE_BINARY_DIR}/resources COPYONLY)
#configure_file ("my_file2.jpg" ${CMAKE_BINARY_DIR}/resources COPYONLY)
configure_file ("Font/Candy_Pop!-demo-font.ttf" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Font/Asdonuts.ttf" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("Backgrounds/NextLevel.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Backgrounds/GameOver.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Image/Cat.png" ${CMAKE_BINARY_DIR} COPYONLY)

