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
        return Range([foo(x) for x in self.provider])

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

    def ToList(self):
        return list(self.provider)

print((Range(generateFibonacci())
       .Where(lambda x: x % 3 == 0))
      .Take(5)
      .ToList())