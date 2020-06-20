
template<typename T>
T add(T a, T b)
{
  return a + b;
}

int main(void)
{
  add(1, 2);
  add('a', 'b');
  add<double>(1, 2);

  return 0;
}
