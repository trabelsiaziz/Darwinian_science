

#include <bits/stdc++.h>


using namespace std;

#define LOCAL
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "


#define arr array
#define ll long long
#define ld long double
#define sz(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define f first 
#define s second
#define pb push_back
#define mp make_pair
#define endl '\n' 
#define NO cout << "NO" << endl
#define YES cout << "YES" << endl
#define read(v) for (auto &u : v) cin >> u;
#define print(v) for (auto u : v) cout << u << ' ';
#define int ll 


// Hyper params

const int GENERATION_SIZE = 50; 
const int POPULATION_SIZE = 200; 
const double CROSSOVER_RATE = 0.75; 
const double MUTATION_RATE = 0.05; 


// problem data
// const vector<int> values = { 5, 6, 4, 6, 5, 2};  // best score is 17
// const vector<int> weights = { 6, 5, 6, 6, 3, 7};  
vector<int> values ; 
vector<int> weights ; 
int GENOME_SIZE; 
int KNAPSACK_CAPACITY;


vector<int> best_genome; 
int best_fitness = 0; 


vector<int> get_genome(int gen_size){
  
  mt19937 rng(random_device{}());             
  uniform_int_distribution<int> dist(0, 1);

  vector<int> genome;   
  for(int j = 0; j < gen_size; j++){
    genome.pb(dist(rng)); 
  }

  return genome; 
}

vector<vector<int>> init_population(int pop_size, int gen_size){

  vector<vector<int>> population; 
  for(int i = 0; i < pop_size ; i++){
    population.pb(get_genome(gen_size)); 
  }
  
  return population; 
}



int get_fitness(vector<int> genome){
  
  // we wanna maximize the value and minimize the corresponding weight
  // i guess sum of selected values is a good start 
  // but we need to consider the knapsack capacity 
  
  int fitness = 0; 
  int total_weight = 0; 
 
  for(int i = 0 ; i < GENOME_SIZE ; i++) {
    fitness += genome[i] * values[i];
    total_weight += genome[i] * weights[i]; 
  }

  return (total_weight > KNAPSACK_CAPACITY ? 0 : fitness); 
}

vector<vector<int>> cross_over(vector<int> parent_one, vector<int> parent_two){
  const int intersection_point = GENOME_SIZE / 2; 

  // check for crossover possibility !! 
  
  mt19937 rng(random_device{}()); 
  uniform_real_distribution<double> dist(0.0, 1.0);
  double x = dist(rng);
  
  if(x > CROSSOVER_RATE) return {parent_one, parent_two}; 


  vector<int> offspring_one, offspring_two; 
  for(int i = 0 ; i < intersection_point ; i++) offspring_one.pb(parent_one[i]);
  for(int i = 0; i < intersection_point ; i++) offspring_two.pb(parent_two[i]); 
  for(int i = intersection_point ; i < GENOME_SIZE ; i++) offspring_one.pb(parent_two[i]); 
  for(int i = intersection_point ; i < GENOME_SIZE ; i++) offspring_two.pb(parent_one[i]); 

  return {offspring_one, offspring_two}; 

}



vector<int> mutate(vector<int> genome){
  
  mt19937 rng(random_device{}()); 
  uniform_real_distribution<double> dist(0.0, 1.0);
  
  for(int& gene : genome){

    double x = dist(rng);
    if(x > MUTATION_RATE) continue;
    gene ^= 1; 
  }

  return genome; 
}

void init_params(){
  
  cin >> GENOME_SIZE; 
  cin >> KNAPSACK_CAPACITY; 

  for(int i = 0; i<GENOME_SIZE ; i++){
    int x; 
    cin >> x; 
    weights.pb(x);   
  }

  for(int i = 0; i<GENOME_SIZE ; i++){
    int x; 
    cin >> x; 
    values.pb(x); 
  }
  
}

void genetic_algo(){

  init_params(); // O(GENOME_SIZE)


  vector<vector<int>> population = init_population(POPULATION_SIZE, GENOME_SIZE); 

  // some good individuals to avoid starting with all zero fitness !! 
  vector<int> indiv1(GENOME_SIZE, 0), indiv2(GENOME_SIZE, 0);
  indiv1[0] = 1; 
  indiv2[1] = 1;   
  population[0] = indiv1; 
  population[1] = indiv2; 

  for(int _ = 0 ; _ < GENERATION_SIZE ; _++){

    cout << "current generation : " << _ << endl; 

    // selection 
    vector<int> luck_wheel;
    int tmp = 0; 
    for(auto indiv : population) {
      int fit = get_fitness(indiv); 
      if(fit > best_fitness){
        best_fitness = fit; 
        best_genome = indiv; 
      } 

      tmp += fit; 
      luck_wheel.pb(tmp); 
    } 
    
    mt19937 rng(random_device{}()); 
    uniform_int_distribution<int> dist(0, luck_wheel.back());
    
    vector<vector<int>> new_population;  
    
    for(int __ = 0; __ < GENERATION_SIZE / 2 ; __++) {
      
      int parent_one_index = lower_bound(luck_wheel.begin(), luck_wheel.end(), dist(rng)) - luck_wheel.begin(); 
      int parent_two_index; 
     
      while(true) {
        parent_two_index = lower_bound(luck_wheel.begin(), luck_wheel.end(), dist(rng)) - luck_wheel.begin(); 
        if(parent_two_index != parent_one_index) break; 
      }

      vector<vector<int>> offsprings = cross_over(population[parent_one_index], population[parent_two_index]);  
      
      for(vector<int> offspring : offsprings){
        new_population.pb(mutate(offspring)); 
      }
    }

    population = new_population; 

  }

}


int32_t main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0); cout.tie(0);
  cout << fixed << setprecision(15);
  
  genetic_algo(); 

  debug() << imie(best_fitness); 
  debug() << imie(best_genome);  

}
