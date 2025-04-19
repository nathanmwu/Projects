% Characters and affiliations
character(luke_skywalker, jedi).
character(darth_vader, sith).
character(yoda, jedi).
character(princess_leia, rebel).
character(han_solo, smuggler).

% Relationships
mentor(yoda, luke_skywalker).
mentor(darth_vader, luke_skywalker).
ally(princess_leia, han_solo).
ally(luke_skywalker, princess_leia).
enemy(luke_skywalker, darth_vader).

% Rules
% Rule 1: Two characters are teammates if they are allies or if they share a mentor.
teammates(X, Y) :- ally(X, Y).
teammates(X, Y) :- mentor(Z, X), mentor(Z, Y), X \= Y.

% Rule 2: Two characters are rivals if one is a Jedi and the other is a Sith, and they are enemies.
rivals(X, Y) :- character(X, jedi), character(Y, sith), enemy(X, Y).
