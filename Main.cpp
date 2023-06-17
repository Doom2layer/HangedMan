#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>

void printmessage(std::string message, bool printtop = true, bool printbottom = true)
{
 bool front = true;

 if (printtop)
 {
  std::cout << "+-----------------------------+" << std::endl;
  std::cout << "|";
 }
 else
 {
  std::cout << "|";
 }
 for (int i = message.length(); i < 29; i++)
 {
  if (front)
  {
   message = " " + message;
  }
  else
  {
   message = message + " ";
  }
  front = !front;
 }
 std::cout << message.c_str();

 if (printbottom)
 {
  std::cout << "|" << std::endl;
  std::cout << "+-----------------------------+" << std::endl;
 }
 else
 {
  std::cout << "|" << std::endl;
 }
}
void DrawHangman(int guesscount = 0)
{
 if (guesscount >= 1)
  printmessage("|", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount >= 2)
  printmessage("|", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount >= 3)
  printmessage("O", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount == 4)
  printmessage("/", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount == 5)
  printmessage("/|", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount >= 6)
  printmessage("/|\\", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount >= 7)
  printmessage("|", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount == 8)
  printmessage("|", false, false);
 else
  printmessage(" ", false, false);
 if (guesscount >= 9)
  printmessage("/ \\", false, false);
 else
  printmessage(" ", false, false);
}
void printLetters(std::string input, char from, char to)
{
 std::string s;
 for (char i = from; i <= to; i++)
 {
  if (input.find(i) == std::string::npos)
  {
   s += i;
   s += " ";
  }
  else
  {
   s += " ";
  }
 }
 printmessage(s, false, false);
}
void printavailaveletters(std::string taken)
{
 printmessage("Available Letters");
 printLetters(taken, 'a', 'm');
 printLetters(taken, 'n', 'z');
}
bool printWorkCheckWin(std::string word, std::string guessed)
{
 bool won = true;
 std::string s;
 for (int i = 0; i < word.length(); i++)
 {
  if (guessed.find(word[i]) == std::string::npos)
  {
   won = false;
   s += "_";
  }
  else
  {
   s += word[i];
   s += " ";
  }
 }
 printmessage(s, false, false);
 return won;
}
std::string loadrandomword(std::string path)
{
 int linecount = 0;
 std::string word;
 std::vector<std::string> v;
 std::ifstream reader(path);
 if (reader.is_open())
 {
  while (std::getline(reader, word))

   v.push_back(word);
  int randline = rand() % v.size();
  word = v.at(randline);
  reader.close();
 }
 return word;
}

int triesLeft(std::string word, std::string guess)
{
 int error = 0;
 for (int i = 0; i < guess.length(); i++)
 {
  if (word.find(guess[i]) == std::string::npos)
   error++;
 }
 return error;
}

int main()
{

 srand(time(0));
 std::string guesses;
 std::string wordToGuess;
 wordToGuess = loadrandomword("words.txt");
 int tries = 0;
 bool win = false;
 do
 {
  system("cls");
  printmessage("HANGMAN");
  DrawHangman(tries);
  printavailaveletters(guesses);
  printWorkCheckWin(wordToGuess, guesses);
  if (triesLeft(wordToGuess, guesses) >= 9)
   break;
  char x;
  std::cout << ">";
  std::cin >> x;
  if (guesses.find(x) == std::string::npos)
   guesses += x;
  tries = triesLeft(wordToGuess, guesses);
  if (printWorkCheckWin(wordToGuess, guesses))
  {
   win = true;
   break;
  }
 } while (tries < 10);
 if (win)
  printmessage("YOU WON!");
 else
  printmessage("GAME OVER");
 system("pause");
 return 0;
}
