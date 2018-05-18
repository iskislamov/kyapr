def generateFibonacci():
    first = 1
    second = 1
    while True:
        second += first
        first = second - first
        yield second

class Range:
    def __init__(self, provider):
        self.provider = provider

    def Select(self, foo):
        return Range([foo(x) for x in self.provider()])

    def Flatten(self):
        return Range([y for x in self.provider for y in x])

    def Where(self, predicate):
        return Range(filter(predicate, self.provider))

    def Take(self, count):
        return Range(self.generate(count))

    def generate(self, count):
        iteration = 0
        for x in self.provider:
            if iteration == count:
                break
            iteration += 1
            yield x

    def OrderBy(self, foo):
        return Range(sorted(self.provider, key=foo))

    def GroupBy(self, foo):
        d = {}
        for elem in self.provider():
            if foo(elem) not in d:
                d[foo(elem)] = []
            d[foo(elem)].append(elem)
 
        def generator():
            for key, elems in d.items():
                yield key, elems
 
        return Range(generator)    

    def ToList(self):
        return list(self.provider)

print((Range(generateFibonacci())
       .Where(lambda x: x % 3 == 0))
      .Take(5)
      .ToList())


with open("somepoem.txt", "r") as input:
    def generator():
        for line in input:
            words = [word for word in line.strip().split(' ') if word]
            for word in words:
                yield word

    print(Range(generator)
          .GroupBy(lambda x: x)
          .Select(lambda x: (len(x[1]), x[0]))
          .OrderBy(lambda x: x[0])
          .ToList())