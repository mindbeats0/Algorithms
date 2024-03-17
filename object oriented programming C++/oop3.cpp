int main() {

  int* y = new int;//Grabs a new space
  *y = 500;        //Sets the newly allocated data to 500
  delete y;


  int* x = new int[5000]; //Declares a large new int array - new returns a pointer
  x[50] = 10; x[10] = 50; //Do stuff with new array -- acts no different
  delete[] x;             //[] denotes x points to an array rather than single var
  return 0;
}
