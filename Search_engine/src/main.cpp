#include "mainwindow.h"
#include "include/server.h"
#include <iostream>
#include <QApplication>




int main(int argc, char *argv[])
{
   ConverterJSON converter;
   InvertedIndex index;
   std::vector<std::string> a = converter.GetTextDocuments();
   index.UpdateDocumentBase(converter.GetTextDocuments());
   SearchServer server(index);

}




