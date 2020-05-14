// Copyright Lebedev Alexander 2020
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    
  QApplication app(argc, argv);  
    
  Experement window;
 
  window.resize(1080, 720);
  window.setWindowTitle("Experiment");
  window.show();
 
  return app.exec();
}