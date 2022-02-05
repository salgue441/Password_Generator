#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <ctime>

static const char alphanumeric[] = "123456789" "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "!@#$%^&*(),.<>?/|~";
int stringLength = sizeof(alphanumeric);

// program functions 
void menu();
char pickRandom();
void generatePassword(int);
void save_password_file(char*);
void view_saved_passwords();

int main()
{
  int menu_choice = 0, default_size = 12, user_size_input,
      user_choice_input;

  while (menu_choice != 3)
  {
    menu();
    std::cout << "Type the number of the command you wish to do: ";
    std::cin >> menu_choice;

    switch (menu_choice)
    {
    case 1: // generate password
      std::cout << "Choose your password size: " 
        << "\n1. Default size. \n2. Custom size. " << std::endl;
      std::cin >> user_choice_input;

      if (user_choice_input == 2)
      {
        std::cout << "Type the length of the passwords"
          << " (greater than 12 characters): ";
        std::cin >> user_size_input;

        if (user_size_input <= 12)
          generatePassword(default_size);
        else
          generatePassword(user_size_input);
      }
      break;
    case 2: // showing saved passwords
      std::cout << "Showing saved passwords: " << std::endl;
      view_saved_passwords();
      break;
    case 3: // exit message
      std::cout << "Exit complete" << std::endl;
      break;
    // default condition
    default: break;
    } // end of switch loop
  } // end of while loop

  return 0;
}

/*
Shows a simple menu to the user. Choices include: start the program
(initialize the password generation), view saved passwords (shows
the user the passwords saved in a .txt file), and the third option 
[exit program] which closes the program.
params: no parameters needed
*/
void menu()
{
  std::cout << "Terminal Password Generator" << std::endl
    << "Menu: " << std::endl
    << "1. Start Program \n2. View saved passwords \n3. Exit program"
    << std::endl;
}

/*
Picks random characters from the alphanumeric array declared globally. 
It uses the srand function to randomly pick characters (without
duplicating them in every run).
params: no parameters needed
*/
char pickRandom()
{
  return alphanumeric[rand() % stringLength];
}

/*
Generates a password by calling the pickRandom function. It creates
a new array called password_array for distributing into the save
password into a file function and showing it to the user. To generate
the password, it uses a for loop to iterate from 0 to the password size
given by the user_size_input variable (at main())
params:
  - password_size: type int, it's the amount of characters the password
   will have
*/
void generatePassword(int password_size)
{
  char password_array[password_size];

  srand(time(0));
  for (int i = 0; i < password_size; i++)
  {
    password_array[i] = pickRandom();
    save_password_file(password_array);
    std::cout << password_array[i];
  }
  
  std::cout << std::endl; // break line
}

/*
Saves the generated password to a .txt file for keeping tabs at 
which passwords where generated. 
*/
void save_password_file(char* password_array)
{
  std::ofstream password_file;
  password_file.open("password_file.txt", std::ios::out);

  // time and date based on current system
  time_t now = time(0);
  char* dt = ctime(&now); // converting now to string form

  // saving information to file
  if (!password_file)
  {
    std::cout << "Error! The file does not exist";
    return;
  }
  else
  {
    password_file << "Generated password at: " << dt;
    password_file << password_array;
    password_file << std::endl;
  }

  password_file.close(); // closing file
}

/*
Shows the saved passwords from the .txt file created in the
save_password_file function. 
params: no parameters required
*/
void view_saved_passwords()
{
  std::ifstream password_file;
  password_file.open("password_file.txt", std::ios::in);

  std::string get_content;

  if (password_file.is_open())
  {
    while (std::getline(password_file, get_content))
    {
      std::cout << get_content << std::endl;
    } // end of while loop
  } // end of if statement
}
