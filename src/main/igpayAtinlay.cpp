#include <iostream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <cstdio>
// need to include your memory pool header here
#include "listString.h"

using namespace std;

// maximum number of strings available
constexpr int maxNumberOfWords = 15;

/**
 * Magic print funtion: prints the prompt to stdout iff stdin is a TTY
 * (terminal). Print the prompt only if input is NOT redirected.
 *
 * @param prompt string to (potentially) display.
 */
void conditionalStringToStdout(const string& prompt) {
  if (isatty(fileno(stdin)))
    cout << prompt;
}

/**
 * Get the index (in the inUse array) of a free (not in use) entry.
 *
 * @param inUse the array of booleans marking which entries are in use
 * and which are free.
 * @return the lowest valid idex of a free entry (with a false value)
 * or -1 if there is no free index
 */
auto freeStringIndex(bool inUse[maxNumberOfWords]) {
  auto freeIndex = -1;
  for (auto index = 0; freeIndex < 0 && index < maxNumberOfWords; ++index)
    if (!inUse[index])
      freeIndex = index;
  return freeIndex;
}

/**
 * Check that index is both in range (on range [0, maxNumberOfWords)) and in use.
 *
 * @param inUse the array of strings that are in use
 * @param index array index to check
 * @return true if in range and in use; false otherwise
 *
 * @note THIS FUNCTION CHECKS AND PRINTS ERROR MESSAGES. This is a bad
 * code smell. It would be better to split this apart into a checker
 * and a reporter. That way indices could be checked without
 * generationg any output. Output would be handled at a different
 * level of abstraction. This is a HACK.
 */
bool validateStringIndex(bool inUse[maxNumberOfWords], int index) {
  if ((0 <= index) && (index < maxNumberOfWords)) {
    if (inUse[index]) {
      return true;
    } else
      cout << "String index " << index << " contains no string.\n";
  } else
    cout << index << " is out of range of valid strings [0, "
         << maxNumberOfWords << ")\n";
  return false;
}

/**
 * main program
 */
int main(int argc, char *argv[])
{
  // initialize the memory pool for all ListString.
  //ListString::setPool(new AbstractMemoryPool());

  // words/inUse are parallel arrays of string/bool
  // inUse[x] -> words[x] is a valid, in use string
  ListString words[maxNumberOfWords];
  bool inUse[maxNumberOfWords] = {false};

  bool myTrace = false;

  // the prompt to display to the user
  string prompt = "Action: (adfinpqst?): ";
  string line;
  conditionalStringToStdout(prompt);
  while (getline(cin, line))
  {
    if (line.empty()) continue;

    stringstream entered(line, ios::in);
    string cmd;

    entered >> cmd; // next word

    if (cmd == "q")
    {
      break;
    } else if (cmd == "a")
    { // add the given word to the list of words if possible
      int freeString = freeStringIndex(inUse);
      if (freeString < 0)
        cout << "No free strings available" << endl;
      else {
        string word;
        entered >> word;

        words[freeString] = ListString{word};
        inUse[freeString] = true;
      }
    } else if (cmd == "d")
    {
      int deleteIndex;
      entered >> deleteIndex;
      if (validateStringIndex(inUse, deleteIndex)) {
        words[deleteIndex] = ListString{};
        inUse[deleteIndex] = false;
      }
    } else if (cmd == "f")
    {
      cout << "Pool Freelist:" << endl;
      ListString::freeList();
      cout << endl;
    } else if (cmd == "i")
    {
      int igpayIndex;
      entered >> igpayIndex;
      if (validateStringIndex(inUse, igpayIndex)) {
        words[igpayIndex].igpayAtinlay();
      }
    } else if (cmd == "n")
    {
      int nodesIndex;
      entered >> nodesIndex;
      if (validateStringIndex(inUse, nodesIndex)) {
        words[nodesIndex].nodes();
      }
    } else if (cmd == "p")
    {
      cout << "words: -----" << endl;
      for (auto index = 0; index < maxNumberOfWords; ++index)
        if (inUse[index])
          cout << "  [" << index << "] = " << words[index] << endl;
      cout << "------------" << endl;
    } else if (cmd == "s")
    {
      int setIndex;
      entered >> setIndex;
      if (validateStringIndex(inUse, setIndex)) {
        string word;
        entered >> word;
        words[setIndex] = ListString{word};
      }
    } else if (cmd == "t")
    {
      myTrace = !myTrace;
      ListString::trace(myTrace);
    } else {
      if (cmd != "?")
        cout << "Unknown command \""<< cmd << "\"" << endl;
      cout << "Valid commands:" << endl;
      cout << "(a)dd\n(d)elete\n(f)ree-list\n(i)gpay-atinizelay\n"
        "(n)odes\n(p)rint\n(q)uit\n(s)et\n(t)race\n(?)help\n";
    }
    conditionalStringToStdout(prompt);
  }
}
