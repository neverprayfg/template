#ifdef IGNORE_THIS_FILE
  system("g++ -std=c++2a wa.cpp -o/wa");
  system("g++ -std=c++2a ac.cpp -o/ac");
  system("g++ -std=c++2a gen.cpp -o/gen");
  for(int i = 1; i <= 50; i++){
    std::cerr << "Test" << i << " : ";
    system("./gen > gen.in");
    system("./ac < gen.in > ac.out");
    system("./wa < gen.in > wa.out");
    if (system("diff ac.out wa.out")) {
      std::cerr << "ERR\n";
      return 0;
    }
    std::cerr << "AC\n";
  }
#endif  