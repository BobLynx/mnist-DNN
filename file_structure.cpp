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
// 	ifstream file (/*full_path*/"C:/Users/Eddie/C++ Projects/mnist DNN/train-images-idx3-ubyte/train-images.idx3-ubyte");
// 	if (file.is_open()){
// 		int magic_number=0;
// 		int number_of_images=0;
// 		int n_rows=0;
// 		int n_cols=0;
// 		file.read((char*)&magic_number,sizeof(magic_number)); 
// 		magic_number = reverseInt(magic_number);
// 		file.read((char*)&number_of_images,sizeof(number_of_images));
// 		number_of_images = reverseInt(number_of_images);
// 		file.read((char*)&n_rows,sizeof(n_rows));
// 		n_rows = reverseInt(n_rows);
// 		file.read((char*)&n_cols,sizeof(n_cols));
// 		n_cols = reverseInt(n_cols);
		
// 		for(int i=0;i<number_of_images;++i){
// 			for(int r=0;r<n_rows;++r){
// 				for(int c=0;c<n_cols;++c){
// 					unsigned char temp=0;
// 					file.read((char*)&temp,sizeof(temp));

// 				}
// 			}
// 		}
// 	}
// }

int main(){
	std::ios_base::sync_with_stdio(false);
	std::ifstream file;
	int mode;
	std::cout << "mode? (test=0, actual=1)";
	std::cin >> mode;
	if(mode){
		file.open("train-images-idx3-ubyte/train-images.idx3-ubyte", std::ios::binary);
	}
	else{
		file.open("txt_in.txt"); //train-images-idx3-ubyte/train-images.idx3-ubyte
	}
	if(file.fail()){
		std::cout << "Error" << "\n";
	}
	else{
		std::cin.get();
		int cnt=0;
		while(cnt<4){
			// std::string cur_str;
			unsigned char cur;
			file.read((char*)&cur, sizeof(cur));
			std::cout << std::bitset<8> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
			// cur_str = cur_str + (char)cur;
			std::cout << (unsigned int)cur << "\n\n";
			cnt+=1;
		}
		std::cin.get();
		unsigned int imgBatchSize = 0;
		while(cnt<8){
			unsigned char cur;
			file.read((char*)&cur, sizeof(cur));
			std::cout << std::bitset<8> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
			std::cout << (unsigned int)cur << "\n\n";
			imgBatchSize = (imgBatchSize << 8);
			imgBatchSize += (unsigned int)cur;
			// std::cin >> cur;
			cnt+=1;
		}
		std::cout << imgBatchSize << "\n\n";
		std::cin.get();
		int imgHeight = 0;
		while(cnt<12){
			unsigned char cur;
			file.read((char*)&cur, sizeof(cur));
			std::cout << std::bitset<8> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
			std::cout << (unsigned int)cur << "\n\n";
			imgHeight = (imgHeight << 8);
			imgHeight += (unsigned int)cur;
			// std::cin >> cur;
			cnt+=1;
		}
		std::cout << imgHeight << "\n\n";
		std::cin.get();
		int imgWidth = 0;
		while(cnt<16){
			unsigned char cur;
			file.read((char*)&cur, sizeof(cur));
			std::cout << std::bitset<8> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
			std::cout << (unsigned int)cur << "\n\n";
			imgWidth = (imgWidth << 8);
			imgWidth += (unsigned int)cur;
			cnt+=1;
		}
		std::cout << imgWidth << "\n\n";
		std::cin.get();
		for(int a=0;a<imgBatchSize;a++){
			for(int i=0;i<imgHeight;i++){
				for(int j=0;j<imgWidth;j++){
					unsigned char cur;
					file.read((char*)&cur, sizeof(cur));
					std::cout << std::setfill(' ') << std::setw(3) << (unsigned int)cur << " "/* << sizeof(cur) << " "*/;
					cnt+=1;
				}
				std::cout << "\n";
			}
			std::cout << "\n";
			std::cin.get();
		}
		// unsigned int cur;
		// file.read((char*)&cur, sizeof(cur));
		// std::cout << std::bitset<32> (cur) << " " << /*" Acutal Reading(from the last bit) " <<*/ sizeof(cur) << "*8" << "\n";
		// std::cout << (unsigned int)cur << "\n\n";
		// std::cin >> cur;
		// while(true){
		// 	for(int i=0;i<28;i++){
		// 		// std::string cur_str;
		// 		unsigned char cur;
		// 		file.read((char*)&cur, sizeof(cur));
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