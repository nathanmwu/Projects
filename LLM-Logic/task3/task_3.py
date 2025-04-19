from pyswip import Prolog

prolog = Prolog()

prolog.consult('star_wars_kb.pl')

print("----Characters----")
# print all characters
for res in prolog.query('character(X, Y)'):
    print(res['X'], ",", res['Y'])

print("\n----Teammates----")
# print all teammates
for res in prolog.query('teammates(X, Y)'):
    print(res['X'], "and", res['Y'])

print("\n----Rivals----")
print("luke_skywalker and darth_vader: ", [] != list(prolog.query('rivals(luke_skywalker, darth_vader)')))
print('luke_skywalker and yoda: ', [] != list(prolog.query('rivals(luke_skywalker, yoda)')))