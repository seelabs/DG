#include <algorithm>
#include <iostream>
#include <vector>

class ChunkTransform
{
public:
    virtual
    std::vector<int>
    transform(std::vector<int> in) = 0;
};

// A collection of transforms
class Transforms
{
    std::vector<ChunkTransform*> transforms_;
public:
    std::vector<int>
    transform(std::vector<int> in)
    {
        std::vector<int> cur = in;
        for (std::vector<ChunkTransform*>::iterator i = transforms_.begin();
             i != transforms_.end();
             ++i)
            cur = (*i)->transform(cur);
        return cur;
    }

    void
    push_back(ChunkTransform* t)
    {
        transforms_.push_back(t);
    }

    // compose transforms
    void
    push_back(Transforms ts)
    {
        for (std::vector<ChunkTransform*>::iterator i = ts.transforms_.begin();
             i != ts.transforms_.end();
             ++i)
        transforms_.push_back(*i);
    }
};

// Sum the first N smallest elements
class SumNChunk : public ChunkTransform
{
    size_t n_ = 0;

public:
    SumNChunk(size_t n) : n_(n)
    {
    }

    std::vector<int>
    transform(std::vector<int> in) override
    {
        std::sort(in.begin(), in.end());
        int sum = 0;
        int n = 0;
        for (std::vector<int>::iterator i = in.begin(); i != in.end() && n < n_;
             ++i, ++n)
        {
            sum += *i;
        }
        std::vector<int> result;
        result.push_back(sum);
        return result;
    }
};


int
main(int argc, char** argv)
{
    std::vector<int> test({3, 4, 5, 1, 2, 3, 11});
    Transforms t1;
    t1.push_back(new SumNChunk(3));
    std::vector<int> r = t1.transform(test);
    std::cout << "Result is: " << r[0] << '\n';

    Transforms t2;
    t2.push_back(t1);
    std::vector<int> r2 = t2.transform(test);
    std::cout << "Result is: " << r2[0] << '\n';

    return 0;
}
