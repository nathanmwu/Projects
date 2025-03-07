class BackwardChainer:
    def __init__(self, rules, assertions):
        self.rules = rules  # list of (antecedents, consequent) tuples
        self.assertions = assertions  # Set of known facts

    def substitute(self, expression, bindings):
        # replace variables in an expression based on bindings
        for var, value in bindings.items():
            expression = expression.replace(var, value)
        return expression

    def find_bindings(self, pattern, fact):
        # find variable bindings that make pattern match fact
        pattern_split = pattern.split()
        fact_split = fact.split()
        if len(pattern_split) != len(fact_split):
            return None
        bindings = {}
        for p, f in zip(pattern_split, fact_split):
            if p.startswith("(?"):
                bindings[p] = f
            elif p != f:
                return None
        return bindings

    def backward_chain(self, goal):
        # recursive backward chaining to prove a goal
        
        # print("PROVE: ", goal)
        
        # 1. check if goal is directly asserted
        if goal in self.assertions:
            # print("Goal is in assertions")
            return True
        
        # print("Goal has not been seen")
        # print("Finding matching consequent")

        # 2. try to find a rule with matching consequent
        for rule in self.rules:
            antecedent, consequent = rule
            bindings = self.find_bindings(consequent, goal)
            if bindings is not None:
                # print("Matching consequent found")
                # print(consequent, bindings)
                antecedent_sub = [self.substitute(a, bindings) for a in antecedent]
                # print(antecedent_sub)
                if all(self.backward_chain(a) for a in antecedent_sub):
                    return True
        # 3. if no rules apply, goal is assumed false
        # print("Matching consequent for goal '", goal, "' could not be found")
        return False

# zookeeper knowledge base
rules = [
    (("(?x) has hair",), "(?x) is a mammal"),
    (("(?x) gives milk",), "(?x) is a mammal"),
    (("(?x) has feathers",), "(?x) is a bird"),
    (("(?x) flies", "(?x) lays eggs"), "(?x) is a bird"),
    (("(?x) is a mammal", "(?x) eats meat"), "(?x) is a carnivore"),
    (("(?x) is a mammal", "(?x) has pointed teeth", "(?x) has claws", "(?x) has forward-pointing eyes"), "(?x) is a carnivore"),
    (("(?x) is a mammal", "(?x) has hoofs"), "(?x) is an ungulate"),
    (("(?x) is a mammal", "(?x) chews cud"), "(?x) is an ungulate"),
    (("(?x) is a carnivore", "(?x) has tawny color", "(?x) has dark spots"), "(?x) is a cheetah"),
    (("(?x) is a carnivore", "(?x) has tawny color", "(?x) has black stripes"), "(?x) is a tiger"),
    (("(?x) is an ungulate", "(?x) has long legs", "(?x) has long neck", "(?x) has tawny color", "(?x) has dark spots"), "(?x) is a giraffe"),
    (("(?x) is an ungulate", "(?x) has white color", "(?x) has black stripes"), "(?x) is a zebra"),
    (("(?x) is a bird", "(?x) does not fly", "(?x) has long legs", "(?x) has long neck", "(?x) has black and white color"), "(?x) is an ostrich"),
    (("(?x) is a bird", "(?x) does not fly", "(?x) swims", "(?x) has black and white color"), "(?x) is a penguin"),
    (("(?x) is a bird", "(?x) is a good flyer"), "(?x) is an albatross"),
]

# test assertions
assertions = {
    "tim has feathers", "tim is a good flyer",
    "mark flies", "mark does not fly", "mark lays eggs", "mark swims", "mark has black and white color",
    "remi gives milk", "remi eats meat", "remi has tawny color", "remi has dark spots",
    "tigger gives milk", "tigger eats meat", "tigger has tawny color", "tigger has black stripes",
    "bambi has hair", "bambi chews cud", "bambi has black stripes", "bambi has white color"
}

bc = BackwardChainer(rules, assertions)

# tests for match method
assert(True == bc.backward_chain("tim has feathers"))
assert(True == bc.backward_chain("tim is a good flyer"))
assert(True == bc.backward_chain("mark does not fly"))
assert(True == bc.backward_chain("mark lays eggs"))
assert(True == bc.backward_chain("mark swims"))
assert(True == bc.backward_chain("mark has black and white color"))

# tests recursive backward chaining for multiple layers
assert(True == bc.backward_chain("tim is an albatross"))
assert(True == bc.backward_chain("mark is a penguin"))
assert(True == bc.backward_chain("remi is a carnivore"))
assert(True == bc.backward_chain("remi is a cheetah"))
assert(False == bc.backward_chain("tigger is a cheetah"))
assert(True == bc.backward_chain("tigger is a tiger"))
assert(True == bc.backward_chain("bambi is a zebra"))