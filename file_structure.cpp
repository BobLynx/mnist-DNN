#include <iostream>
#include <fstream>
// #include <string>
#include <bitset>
#include <iomanip>

// int reverseInt (int i) 
// {
// 	unsigned char c1, c2, c3, c4;

// 	c1 = i & 255;
// 	c2 = (i >> 8) & 255;
// 	c3 = (i >> 16) & 255;
// 	c4 = (i >> 24) & 255;

// 	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
// }
// void read_mnist(/*string full_path*/)
// {
// 	ifstream image (/*full_path*/"C:/Users/Eddie/C++ Projects/mnist DNN/train-images-idx3-ubyte/train-images.idx3-ubyte");
// 	if (image.is_open()){
// 		int magic_number=0;
// 		int number_of_images=0;
// 		int n_rows=0;
// 		int n_cols=0;
// 		image.read((char*)&magic_number,sizeof(magic_number)); 
// 		magic_number = reverseInt(magic_number);
// 		image.read((char*)&number_of_images,sizeof(number_of_images));
// 		number_of_images = reverseInt(number_of_images);
// 		image.read((char*)&n_rows,sizeof(n_rows));
// 		n_rows = reverseInt(n_rows);
// 		image.read((char*)&n_cols,sizeof(n_cols));
// 		n_cols = reverseInt(n_cols);
		
// 		for(int i=0;i<number_of_images;++i){
// 			for(int r=0;r<n_rows;++r){
// 				for(int c=0;c<n_cols;++c){
// 					unsigned char temp=0;
// 					image.read((char*)&temp,sizeof(temp));

// 				}
// 			}
// 		}
// 	}
// }
int bitreadings_8(int& cnt, std::ifstream& tgt){
	int varSize = 0;
	int maxCount = cnt + 4;
	while(cnt < maxCount){
		// std::string cur_str;
		unsigned char cur = 0;
		tgt.read((char*)&cur, sizeof(cur));
		std::cout << std::bitset<8> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
		// cur_str = cur_str + (char)cur;
		std::cout << (unsigned int)cur << "\n\n";
		varSize = (varSize << 8);
		varSize += (unsigned int)cur;
		cnt+=1;
	}
	return varSize;
}

int main(){
	std::ios_base::sync_with_stdio(false);
	std::ifstream image;
	std::ifstream label;
	int mode;
	std::cout << "mode? (test=0, actual=1)";
	std::cin >> mode;
	if(mode){
		image.open("train-images-idx3-ubyte/train-images.idx3-ubyte", std::ios::binary);
		label.open("train-labels-idx1-ubyte/train-labels.idx1-ubyte", std::ios::binary);
	}
	else{
		image.open("txt_in.txt"); //train-images-idx3-ubyte/train-images.idx3-ubyte
	}
	if(image.fail()){
		std::cout << "Error" << "\n";
	}
	else{
		
		std::cout << "\nImage Definition\n";
		std::cin.get();
		int cnt=0;
		bitreadings_8(cnt, image);
		
		
		std::cin.get();
		unsigned int imgBatchSize = 0;
		imgBatchSize = bitreadings_8(cnt, image);
		std::cout << imgBatchSize << "\n\n";
		
		
		std::cin.get();
		int imgHeight = 0;
		imgHeight = bitreadings_8(cnt, image);
		std::cout << imgHeight << "\n\n";


		std::cin.get();
		int imgWidth = 0;
		imgWidth = bitreadings_8(cnt, image);
		std::cout << imgWidth << "\n\n";
		
		
		std::cout << "\nLabel Definition\n";
		int labelcnt = 0;
		std::cin.get();
		bitreadings_8(labelcnt, label);
		
		
		std::cin.get();
		bitreadings_8(labelcnt, label);
		
		
		// std::cin.get();
		// bitreadings_8(labelcnt, label);
		

		// std::cin.get();
		// bitreadings_8(labelcnt, label);
		

		// while(true){
		// 	std::cin.get();
		// 	bitreadings_8(labelcnt, label);
		// }

		std::cout << "\n\nImages + Label\n";
		std::cin.get();
		for(int a=0;a<imgBatchSize;a++){
			for(int i=0;i<imgHeight;i++){
				for(int j=0;j<imgWidth;j++){
					unsigned char cur;
					image.read((char*)&cur, sizeof(cur));
					std::cout << std::setfill(' ') << std::setw(3) << (unsigned int)cur << " "/* << sizeof(cur) << " "*/;

					cnt+=1;
				}
				std::cout << "\n";
			}
			std::cout << "\n";
			unsigned char curlabel;
			label.read((char*)&curlabel, sizeof(curlabel));
			std::cout << std::setfill(' ') << std::setw(3) << (unsigned int)curlabel << " "/* << sizeof(cur) << " "*/;
			std::cout << "\n";
			std::cin.get();
		}
		// unsigned int cur;
		// image.read((char*)&cur, sizeof(cur));
		// std::cout << std::bitset<32> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
		// std::cout << (unsigned int)cur << "\n\n";
		// std::cin >> cur;
		// while(true){
		// 	for(int i=0;i<28;i++){
		// 		// std::string cur_str;
		// 		unsigned char cur;
		// 		image.read((char*)&cur, sizeof(cur));
		// 		// std::cout << std::bitset<8> (cur) << " Acutal Reading(from the last bit) " << sizeof(cur) << "*8" << "\n";
		// 		// cur_str = cur_str + (char)cur;
		// 		std::cout << std::bitset<8> (cur) << " ";
		// 	}
		// 	std::cin >> cnt;
		// 	std::cout << "\n";
		// }
	}
	return 0;
}