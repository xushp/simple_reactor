#include <iostream>
#include <memory>
#include <map>

using namespace std;

class TestClass {
public:
  TestClass() { cout << "TestClass()" << endl; }
  ~TestClass() { cout << "~TestClass()" << endl; }
};

void auto_do_release()
{
  unique_ptr<TestClass> uni_ptr = unique_ptr<TestClass>(new TestClass());
  unique_ptr<TestClass> another_ptr;
  another_ptr = std::move(uni_ptr);

  uni_ptr = NULL;
  cout << "auto do release end" << endl;
}

int main()
{
  auto_do_release();
  
  return 0;
}
