make_tree_lists_more(nil,_,_):-!.
make_tree_lists_less(nil,_,_):-!.


make_tree_lists_more(Root, [Root, Head | Tail]):-Root > 0.
make_tree_lists_less(Root, [Root, Head | Tail]):-Root < 0.

make_tree_lists(tr(Root,Left,Right), [HeadX|TailX], [HeadY,TailY]):-
(make_tree_lists_more(Root, HeadX);make_tree_lists_less(Root, HeadY)),
make_tree_lists(Left, TailX, TailY);
make_tree_lists(Right, TailX, TailY).