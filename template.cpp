#include <bits/stdc++.h>

using namespace std;

int main() {
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
