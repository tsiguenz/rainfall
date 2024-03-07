#include <cstdlib>
#include <cstring>

class N {
public:
  int operator+(N &rhs) { return this->number + rhs.number; }

  char buffer[100];
  int number;

  N(int n) : number(n) {}

  void setAnnotation(char *buff) {
    std::memcpy(this->buffer, buff, strlen(buff));
  }
};

int main(int ac, char **av) {
  if (ac <= 1)
    exit(1);

  N *n1 = new N(5);
  N *n2 = new N(6);
  n1->setAnnotation(av[1]);
  *n1 + *n2;
}
