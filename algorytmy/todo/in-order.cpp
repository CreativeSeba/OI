//In-order jest głównie używany do przechodzenia przez drzewo binarne w kolejności rosnącej lub malejącej, ale tylko wtedy, gdy mamy do czynienia ze strukturą drzewa binarnego poszukiwań (BST, Binary Search Tree).
//
//W skrócie, jeśli drzewo jest BST, to przejście in-order:
//
//Daje posortowaną listę elementów w porządku rosnącym (gdy odwiedzamy lewe poddrzewo, węzeł, potem prawe poddrzewo).
//Może dać posortowaną listę malejąco, jeśli zastosujemy "odwrócone" in-order, czyli przejdziemy najpierw prawe poddrzewo, potem węzeł, a na końcu lewe poddrzewo.