int SET_B = 0;
int SET_C = 0;
int SET_CASE = 0;// Sets if -i is encountered.
int SET_M = 0;// Sets if -m is encountered.
int SET_V = 0;// SET_V sets if -v is an option.
int input_files = 0;// Number of Files.
int SET_H = 0;// Display File's name if set.
int SET_h = 0;// Doesn't display File's name if set.
int sum = 0;// Offset Bytes.

void inputFilesetter(int d);
void setFor_V();
void setFor_H();
void setFor_h();
void setFor_M();
void setFor_CASE();
void setFor_B();
void resetFor_B();
void resetFor_CASE();
void resetFor_V();
void resetFor_H();
void resetFor_h();
void resetFor_M();
void setInputNumberForFiles(int argc);
