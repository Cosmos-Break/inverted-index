// 倒排索引的制作与使用.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h" 
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;
int main()
{
	int count = 0;
	
	map<string,string> texts;
	TiXmlDocument doc("simplewiki-latest-pages-articles.xml");
	doc.LoadFile();
	/*doc.Print();*/
	TiXmlElement* root = doc.FirstChildElement();//指向xml文档的根元素
	if (root == NULL)//检测根元素存在性
	{
		cerr << "Failed to load file: No root element." << endl;
		doc.Clear();
	}
	//elem指向根的第一个孩子元素
	for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
		if (strcmp(elem->Value(), "page") == 0) { //也可以通过元素名寻找元素
			string id;
			for (TiXmlElement* elem2 = elem->FirstChildElement(); elem2 != NULL; elem2 = elem2->NextSiblingElement()) {
				if (strcmp(elem2->Value(), "id") == 0) {
					id = elem2->FirstChild()->Value();
				}
				if (strcmp(elem2->Value(), "revision") == 0) {
					for (TiXmlElement* elem3 = elem2->FirstChildElement(); elem3 != NULL; elem3 = elem3->NextSiblingElement()) {
						if (strcmp(elem3->Value(), "text") == 0) {
							/*TiXmlNode* node = elem3->FirstChild();*/
							texts.insert(pair<string,string>(id,elem3->FirstChild()->Value()));
							
							/*++count;*/
							/*cout << node->Value() << endl;*/
						}
					}
					

				}
			}

			
		}
	}
	for (auto it = texts.begin(); it != texts.end(); ++it) {
		ofstream outfile("data/"+it->first);
		outfile << it->second;
	}
	cout << count << endl;
	
}
