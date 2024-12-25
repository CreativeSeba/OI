#include <bits/stdc++.h>

using namespace std;

int main() {
    //  .  : Do dostępu do członków obiektu (instancji klasy).
    //  -> : Do dostępu do członków obiektu przez pointer.
    //  :: : Do dostępu do elementów globalnych, statycznych, lub do rozwiązywania
    //Operator :: w C++ jest operatorem zasięgu (ang. scope resolution operator), który pozwala na wyraźne wskazanie, do jakiej przestrzeni nazw lub zasięgu należy dany element.
    //operator "::" jest używany do stattycznych badz stalych elementow klasy, bez instancji. funkcja sync_with_stdio jest statyczna, wiec wywoluje sie ja przez "::"
    //ios_base to klasa bazowa w bibliotece standardowej C++, która zapewnia podstawowe funkcje i ustawienia dla strumieni wejścia i wyjścia (np. cin, cout, ifstream, ofstream).
    //ios_base, cin i cout to są klasy. "<<", ">>" to są zoverloadowane operatory

    // Użycie ios_base::sync_with_stdio(false); przyspiesza operacje I/O,
    // ponieważ wyłącza synchronizację pomiędzy strumieniami C++ (cout, cin) a strumieniami C (printf, scanf).
    // Dzięki temu operacje na cout i cin działają niezależnie, co eliminuje dodatkowy narzut związany z synchronizacją.
    // Ustawienie cin.tie(0) sprawia, że bufor cout nie będzie opróżniany przed odczytem z cin, co również zwiększa wydajność.

    ios_base::sync_with_stdio(false); // Wyłącza synchronizację pomiędzy cout i printf, dzięki czemu działają niezależnie.
    // Dzięki temu unika się potencjalnych problemów z kolejnością wyjścia, gdy oba strumienie są używane w tym samym programie.

    cin.tie(0); // Ustawia cin tak, aby nie był związany z cout. Bufor cout nie będzie opróżniany przed odczytem z cin.
    cout.tie(0); // Ustawia cout tak, aby nie był związany z żadnym innym strumieniem. Bufor cout nie będzie opróżniany automatycznie.

    return 0;
}
/*
#include <bits/stdc++.h>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    return 0;
}
*/
