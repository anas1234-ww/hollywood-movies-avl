#include <iostream>
#include "Avl-tree.h"
#include "movie.h"
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <istream>
//function private

TreeNode<str_film>* Movie::Download_data(std::string& file_name){
				   std::ifstream data_movie(file_name);
				   if (data_movie.is_open()){
				   int id_ = 1;				
     std::string line;
				   	std::string data;
     str_film film;
				   				std::string discard;
				   				std::string header;
				   				getline(data_movie , header);
				   		while(getline(data_movie , line)){
				   						std::stringstream ss(line);
				   						
				   						if (line[0] == '"'){
				   										getline(ss , discard , '"');
				   										getline(ss , film.title , '"');
				   										getline(ss , discard , ',');
				   						}else getline(ss , film.title , ',');
				   						if (film.title.empty()) film.title = "Unknown";
				   						getline(ss , film.LeadStudio , ',');
				   						if (film.LeadStudio.empty()) film.LeadStudio = "Unknown";
				   				getline(ss , data , ',');
				   				if (data.empty()) film.RottenTomatoes = 0;
				   				else film.RottenTomatoes = stoi(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.AudienceScore = 0;
				   				else film.AudienceScore = stoi(data);
				   				getline(ss , film.Story , ',');
				   				if (film.Story.empty()) film.Story = "Unknown";
				   				getline(ss , film.Genre , ',');
				   				if (film.Genre.empty()) film.Genre = "Unknown";
				   				getline(ss , data , ',');
				   				if (data.empty()) film.TheatersOpenWeek = 0;
				   				else film.TheatersOpenWeek = stoi(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.OpeningWeekend = 0.0;
				   				else film.OpeningWeekend = stof(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.BOAvgOpenWeekend = 0;
				   				else film.BOAvgOpenWeekend = stoi(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.DomesticGross = 0.0;
				   				else film.DomesticGross = stof(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.ForeignGross = 0.0;
				   				else film.ForeignGross = stof(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.WorldGross = 0.0;
				   				else film.WorldGross = stof(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.Budget = 0;
				   				else film.Budget = stoi(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.Profitability = 0.0;
				   				else film.Profitability = stof(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.OpenProfit = 0.0;
				   				else film.OpenProfit = stof(data);
				   				getline(ss , data , ',');
				   				if (data.empty()) film.Year = 0;
				   				else film.Year = stoi(data);
				   						film.id = id_;
				   						tree.insert(film);
				   						id_++;
				   		}
				   }
				return tree.RetRoot();
}
TreeNode<str_film>* Movie::Search_film(int Ser_ID){
				str_film ser;
				ser.id = Ser_ID;
				TreeNode<str_film>* cur = tree.Search(ser);
				return cur;
}
void Movie::show_movie(TreeNode<str_film>* root){
				if (root == nullptr) return;
				
				show_movie(root->left);
				std::cout << "------------------------------------" << std::endl;
				std::cout << "The id : " << root->value.id << std::endl;
				std::cout << "The title : " << root->value.title << std::endl;
				std::cout << "------------------------------------" << std::endl;
				show_movie(root->right);
}
void Movie::insert_Nodes_vector(TreeNode<str_film>* root){
				if (root == nullptr) return;
				
				insert_Nodes_vector(root->left);
				ines_film_vec.push_back(root);
				insert_Nodes_vector(root->right);
				
}
void Movie::Comparison_Avl_liner(TreeNode<str_film>* root , int ser_id){
				if (root == nullptr) std::cout << "the tree is empty \n";
				// Search O(log n) in the Avl tree
				auto old_avl = std::chrono::steady_clock::now();
				
				TreeNode<str_film>* cur = Search_film(ser_id);
				
				auto end_avl = std::chrono::steady_clock::now();
				std::chrono::duration<double , std::milli> difference_avl = end_avl - old_avl;
				std::cout << "The speed of the Avl is" << difference_avl.count() << "ms \n";
				// Search O(n) in the vector
				insert_Nodes_vector(root);
				auto old_loop = std::chrono::steady_clock::now();
				for (auto ser_film : ines_film_vec) {
								if (ser_film->value.id == ser_id)    break;
				}
				auto end_loop = std::chrono::steady_clock::now();
				std::chrono::duration<double , std::milli> difference_loop = end_loop - old_loop;
				std::cout << "The speed of the liner is " << difference_loop.count() << "ms \n";
				std::cout << "Avl tree is : " << difference_avl.count() / difference_loop.count() << " faster \n";
				ines_film_vec.clear();
}
TreeNode<str_film>* Movie::show_best_movie(TreeNode<str_film>* root){
			if (root == nullptr) return nullptr;
				TreeNode<str_film>* best_film_left = show_best_movie(root->left);
				TreeNode<str_film>* best_film_right = show_best_movie(root->right);
				if (best_film_left != nullptr && best_film_right != nullptr) {
								if (best_film_left->value.AudienceScore == best_film_right->value.AudienceScore) {
								return (best_film_left->value.RottenTomatoes > best_film_right->value.RottenTomatoes) ? best_film_left : best_film_right;
												
								}
								return (best_film_left->value.AudienceScore > best_film_right->value.AudienceScore) ? best_film_left : best_film_right;
				}
				if (best_film_left != nullptr) return best_film_left;
				if (best_film_right != nullptr) return best_film_right;
				return root;
}
TreeNode<str_film>* Movie::Show_films_specific_year(int year , TreeNode<str_film>* root){
				if (root == nullptr) return nullptr;
				if (root->value.Year == year){
								std::cout << "------------------------------------" << std::endl;
				std::cout << "The id : " << root->value.id << std::endl;
				std::cout << "The title : " << root->value.title << std::endl;
				std::cout << "------------------------------------" << std::endl;
				}
				Show_films_specific_year(year , root->left);
				Show_films_specific_year(year , root->right);
				return root;
}
void Movie::General_statistics(TreeNode<str_film>* root){
				insert_Nodes_vector(root);
				
				int total = 0;
				TreeNode<str_film>* Highest_grossing_film = ines_film_vec.at(0);
				for (size_t i = 0 ; i < ines_film_vec.size() ; i++){
								total += ines_film_vec.at(i)->value.Budget;
								if (Highest_grossing_film->value.Profitability < ines_film_vec.at(i)->value.Profitability) Highest_grossing_film = ines_film_vec.at(i);
				}
				std::cout << "The average film budget is estimated at : " << total /  ines_film_vec.size() << std::endl;
				std::cout << "The highest-grossing film is : " << Highest_grossing_film->value.title << std::endl;
				ines_film_vec.clear();
}

//function public
str_film::str_film(){
				
          title = "Unknown"; 
          LeadStudio = "Unknown"; 
          RottenTomatoes = 0;  
          AudienceScore = 0; 
          Story = "Unknown"; 
          Genre = "Unknown"; 
          TheatersOpenWeek = 0;
          OpeningWeekend = 0.0; 
          BOAvgOpenWeekend = 0; 
          DomesticGross = 0.0;  
          ForeignGross = 0.0;  
          WorldGross = 0.0; 
          Budget = 0;
          Profitability = 0.0;
          OpenProfit = 0.0;
          Year = 0;
								
				}
void Movie::Search_film_employment(){
				int id;
				std::cin.exceptions(std::ios::failbit);
				while(true){
								try{
								std::cout << "enter id : " << std::endl;
								std::cin >> id;
								break;				
				}
								catch(const std::ios_base::failure& e){
												std::cout << "Enter a correct choice" << std::endl;
												std::cin.clear();
												std::cin.ignore(std::numeric_limits<std::streamsize>::max() , '\n');
								}
								
				}
				TreeNode<str_film>* ser = Search_film(id);
				if (ser == nullptr){
								std::cout << "------------------------------------" << std::endl;
								std::cout << "The film is not found" << std::endl;
								std::cout << "------------------------------------" << std::endl;
				} 
				else {
								std::cout << "------------------------------------" << std::endl;
				  std::cout << "The id : " << ser->value.id << std::endl;
				  std::cout << "The title : " << ser->value.title << std::endl;
				  std::cout << "------------------------------------" << std::endl;
				}
}
void Movie::show_best_movie_employment(){
				TreeNode<str_film>* best_movie = show_best_movie(root);
				if (best_movie == nullptr)
				std::cout << "films not found" << std::endl;
				else std::cout << "The best movie is : " << best_movie->value.title << std::endl;
}
void Movie::Comparison_Avl_liner_employment(){
				int id;
				std::cin.exceptions(std::ios::failbit);
				while(true){
								try{
												std::cout << "enter id : " << std::endl;
												std::cin >> id;
												break;
								}
								catch (std::ios_base::failure& e){
												std::cout << "The film is not found" << std::endl;
												std::cin.clear();
												std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
								}
				}
				Comparison_Avl_liner(root , id);
}
void Movie::General_statistics_employment(){
				General_statistics(root);
}
Movie::Movie(std::string file_name){
				root = Download_data(file_name);
}
void Movie::show_movie_employment(){
				show_movie(root);
}
void Movie::Show_films_specific_year_employment(){
				int year;
				std::cout << "enter year : " << std::endl;
				std::cin >> year;
				Show_films_specific_year(year , root);
}