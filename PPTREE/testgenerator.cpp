# include <cstdio>
# include <cstdlib>
# include <ctime>

typedef unsigned long int uli;

uli wrapperRand(uli a, uli b)
{
   if(a < b)
   {
      return (uli)(a + (rand() % (b - a)));
   }
   printf("Error in wrapperRand(): a >= b\n");
   return 0;
}

uli restack(uli *vertices, uli numVertices, uli *center)
{
   uli i = wrapperRand(*center + 1, numVertices + 1);
   uli v = vertices[i];
   vertices[*center] = vertices[i];
   vertices[i] = vertices[*center + 1];
   vertices[*center + 1] = 0;
   (*center)++;
   return v;
}

int main()
{
   srand(time(NULL));
   uli numTests = wrapperRand(1, 8);
   printf("%lu\n", numTests);
   for(uli i = 0; i < numTests; i++)
   {
      uli numVertices = wrapperRand(1, 100001);
      printf("%lu\n", numVertices);
      
      uli *vertices = new uli[numVertices + 1];
      uli center = 0;
      uli v1, v2, w;
      for(uli j = 0; j <= numVertices; j++)
      {
         vertices[j] = j;
      }
      
      v1 = restack(vertices, numVertices, &center);
      while(center < numVertices)
      {
         if(v1 == 0)
         {
            v1 = wrapperRand(0, center);
         }
         v2 = restack(vertices, numVertices, &center);
         w = wrapperRand(0, 1000000001);
         printf("%lu %lu %lu\n", v1, v2, w);
         v1 = 0;
      }
   }   
   
   return 0;
}
