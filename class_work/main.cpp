#include <iostream>

void rmMtx(int ** mtx, size_t m);

int ** makeMtx(size_t m, size_t n)
{
  int ** mtxR = new int * [m];
  size_t created = 0;

  try
  {
    for (size_t i = 0; i < m; ++i)
    {
      mtxR[i] = new int [n];
      ++created;
    }
  }
  catch (const std::bad_alloc &)
  {
    rmMtx(mtxR, created);
    throw;
  }

  return mtxR;
}


int ** transpose(int ** mtx, size_t m, size_t n)
{
  int ** res = new int * [n];
  size_t created = 0;

  try
  {
    for (size_t i = 0; i < n; ++i)
    {
      res[i] = new int [m];
      ++created;
    }
  }
  catch (const std::bad_alloc &)
  {
    rmMtx(res, created);
    throw;
  }

  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      res[j][i] = mtx[i][j];
    }
  }

  return res;
}


void rmMtx(int ** mtx, size_t m)
{
  for (size_t i = 0; i < m; ++i)
  {
    delete [] mtx[i];
  }

  delete [] mtx;
}


void printMtx(int ** mtx, size_t m, size_t n)
{
  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      if (j) std::cout << '_';
      std::cout << mtx[i][j];
    }
    std::cout << '\n';
  }
}

int main()
{
  size_t m = 0;
  size_t n = 0;
  std::cin >> m >> n;
  if (!std::cin || m == 0 || n == 0)
  {
    return 1;
  }

  int ** mtx = nullptr;
  try
  {
    mtx = makeMtx(m, n);
  }
  catch (const std::bad_alloc &)
  {
    return 2;
  }

  for (size_t i = 0; i < m; ++i)
  {
    for (size_t j = 0; j < n; ++j)
    {
      std::cin >> mtx[i][j];
    }
  }

  if (std::cin.fail())
  {
    rmMtx(mtx, m);
    return 1;
  }

  int ** t = nullptr;
  try
  {
    t = transpose(mtx, m, n);
  }
  catch (const std::bad_alloc &)
  {
    rmMtx(mtx, m);
    return 2;
  }

  rmMtx(mtx, m);
  mtx = t;

  size_t newM = n;
  size_t newN = m;

  printMtx(mtx, newM, newN);

  rmMtx(mtx, newM);
}
