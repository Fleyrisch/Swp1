#include <stdio.h>
#include <stdlib.h>

enum Bool;
struct OldNew;


// vorausdefinition der verwendeten Funktionen damit der Compiler diese beim Compilieren kennt.

int length(char *s);
char* normalisiere(char* s);
void copy(char* s, int n, char* t);
char* copyStr(char* s);
char* putFront(char c, char* s);
char* reverse(char* s);
char* putBack(char c, char* s);
char* rev(char* s);
void replace(char* s, struct OldNew* m, int n);
char* show(enum Bool b);
enum Bool strCmp(char* s1, char* s2);



// Anzahl aller Zeicher (ohne Null-terminator).
int length(char *s) {
	int n = 0;              // Länge auf 0 initialisieren
	while(*s != '\0') {     // Solange kein endzeichen
		n++;                // Weiteres Zeichen zählen
		s++;                // Zeiger auf des nächste Zeichen in der Zeichenkette verschieben
	}

	return n;               // Länge der Zeichenkette zurückgeben
}


// Normalisiere C String.
// 1. Eliminiere Leerzeichen.
// 2. Alle Grossbuchstaben werden in Kleinbuchstaben umgewandelt.
// 3. Kleinbuchstaben bleiben unveraendert.
// Annahme: C String besteht nur aus Klein-/Grossbuchstaben und Leerzeichen.
char* normalisiere(char* s) {
    int newLen = 0;
    
    int readPtr = 0;
    int writePtr = 0;
    
    while (s[readPtr] != '\0') {
        if (s[readPtr] != ' ') {
            newLen++;
        }
        readPtr++;
    }
    readPtr = 0;
    
    char* r = (char*)malloc(sizeof(char) * (newLen+1));
    
    while (s[readPtr] != '\0') {
        if (s[readPtr] != ' ') {
            if (s[readPtr] >= 'A' && s[readPtr] <= 'Z') {
                r[writePtr] = s[readPtr] + ('a' - 'A');  // Großbuchstabe → klein
            } else {
                r[writePtr] = s[readPtr];  // Kleinbuchstabe bleibt
            }
            writePtr++;
        }
        readPtr++;
    }
    
    r[writePtr] = '\0';
    return r;
}


// Kopiere n Zeichen von s nach t.
// Annahme: n ist > 0
void copy(char* s, int n, char* t) {
	int i = 0;
	while(i < n) {          // Solange Index (i) kleiner als die Zeichenmenge (n)
		t[i] = s[i];        // kopiere ein Zeichen von der Quelle zun Ziel
		i++;                // index um eins verschieben
	}
}


// Baue neuen String welcher eine Kopie des Eingabestrings ist.
char* copyStr(char* s) {
	const int n =  length(s);
	char* r = (char*)malloc(sizeof(char) * (n+1));
	copy(s, n, r);
	r[n] = '\0';
	return r;
}

// Baue neuen String welcher mit Zeichen c startet gefolgt von allen Zeichen in s.
char* putFront(char c, char* s) {
	const int n =  length(s);                         // Länge der Zeichenkette ermitteln (ohne Terminator)
	char* r = (char*)malloc(sizeof(char) * (n+2));    // Platz für die Neue Zeichenkette auf dem Heap reservieren (+ extra zeichen + Terminator)
	copy(s, n+1, r+1);    // Zeichenkette Kopieren, ein zeichen mehr (n+1) ab den ersten (nicht den Nullten!) Zeichen (r+1) auffüllen
	r[0] = c;             // das nullte Zeichen einsetzen
	return r;
}


// Umkehrung eines Strings.
char* reverse(char* s) {
	const int n = length(s);          // Länge der Zeichenkette ermitteln (ohne Terminator)
	char* t = (char*)malloc(sizeof(char) * (n+1));   // Platz für die neue Zeichenkette auf dem Heap reservieren (+ Terminator)
	int i;

	for(i = 0; i < n; i++) {          // für alle Zeichen außer dem nulterminator
		t[i] = s[n-1-i];              // Zeichen von hinten nach vorne Kopieren (n-i) und auch ohne den Terminator (-1)
	}
	t[n] = '\0';                      // Terminator in der umgekehrten Zeichenkette einsetzen

	return t;
}

// Baue neuen String welcher aus allen Zeichen in s besteht gefolgt von Zeichen c.
char* putBack(char c, char* s) {
	char* rev1 = reverse(s);
    char* front = putFront(c, rev1);
    char* result = reverse(front);
    
    free(rev1);
    free(front);
    
    return result;
}


// Baue einen neuen String welcher die Umkehrung des Eingabestrings ist.
// Hinweis: Die Implementierung soll rekursiv sein und die Hilfsroutine putBack verwenden.
char* rev(char* s) {
	// String ist leer
	if (*s == '\0') {
        char* leer = (char*)malloc(sizeof(char));
        leer[0] = '\0';
        return leer;
    }

    char* reversedStr = rev(s + 1);

    char* ergebnis = putBack(*s, reversedStr);

    free(reversedStr);

    return ergebnis;
}


struct OldNew {
	char old;     // zu ersetzendes Zeichen
	char new;     // einzusetztendes Zeichen
};


// Ersetze in einem String jedes Zeichen 'old' mit dem Zeichen 'new'.
// Die Zeichen 'old' und 'new' sind definiert in einem Array vom Typ struct OldNew.
char* replace(char* s, struct OldNew* m, int n) {
    char* r = copyStr(s);
    
    int i = 0;
    
    while (r[i] != '\0') {
        for (int j = 0; j < n; j++) {
            if (r[i] == m[j].old) {
                r[i] = m[j].new;
            }
        }
        i++;
    }
    
    return r;
}

enum Bool {
	True = 1,
	False = 0
};

char* show(enum Bool b) {
	if(b == True) {
		return copyStr("True");
	} else {
		return copyStr("False");
	}
}


// Teste ob zwei Strings identisch sind.
enum Bool strCmp(char* s1, char* s2) {
	while(*s1 == *s2) {
		if(*s1 == '\0' && *s2 == '\0') {
			return True;
		}
		if(*s1 == '\0') {
			return False;
		}
		if(*s2 == '\0') {
			return False;
		}
		s1++;
		s2++;
	}

	return False;
}


void userTests() {
	printf("\n\n *** User Tests *** \n\n");

	char s1[] = "Ha Ll o o ";

	printf("\n1. %s", s1);

	printf("\n2. %s", normalisiere(s1));

	char* s2 = (char*)malloc(length("Hello")+1);

	char* s3 = copyStr("Hello");

	printf("\n3. %s", s3);

	char s4[] = "abcd";

	char* s5 = putBack('!',s4);

	printf("\n4. %s", s5);

	char* s6 = rev(s5);

	printf("\n5. %s", s6);

	char s7[] = "Aa dss fBB";

	printf("\n6. %s", s7);

	struct OldNew m[] = { {'B', 'b'}, {'s', '!'}};

	replace(s7, m, 2);

	printf("\n7. %s", s7);

	char s8[] = "HiHi";

	char* s9 = copyStr(s8);

	enum Bool b1 = strCmp(s8,s9);

	char* s10 = show(b1);

	printf("\n8. %s", s10);

	char s11[] = "HiHo";

	enum Bool b2 = strCmp(s9, s11);

	char* s12 = show(b2);

	printf("\n8. %s", s12);

	free(s2);
	free(s3);
	free(s5);
	free(s6);
	free(s9);
	free(s10);
	free(s12);
}

struct TestCase_ {
	char* input;
	char* expected;
};

typedef struct TestCase_ TC;

void runTests(TC* tc, int n, char* sut(char*)) {
	int i;

	for(i=0; i<n; i++) {
		char* result = sut(tc[i].input);
		if(True == strCmp(tc[i].expected, result)) {
			printf("\n Okay Test (%s,%s) => %s", tc[i].input,tc[i].expected, result);
		} else {
			printf("\n Fail Test (%s,%s) => %s", tc[i].input,tc[i].expected, result);
		}
		free(result);
	}

}


void unitTests() {
	printf("\n\n *** Unit Tests *** \n\n");

	TC normTests[] = {
		{"hElLo", "hello"},
		{"hEl Lo", "hello"},
		{"h  El Lo", "hello"},
	};


	runTests(normTests, 3, normalisiere);

}

char* rndString() {
	int i;
	int n = (rand() % 10) + 1; // Länge der Zeichenkette auslösen (+1 dammit kein leerer String entsteht)
	char* s = (char*)malloc(n+1);     // Gewünschten Platz reservieren

	for(i=0; i<n; i++) {              // für alle Zeichen
		int lowHigh = (rand() % 2) ? 'a' : 'A';  // Auslösen ob gross oder klein Buchstabe
		int c = rand() % 26;                    // Buchstabe auslösen
		s[i] = (char)(c + lowHigh);             // Buchstabe einsetzen 'a'+1 = 'b' , 'a' + 4 = 'e'
	}
	s[n] = '\0';              // Zeilenumsprung einsetzen ?? BUG ?? sollte es an dieser Stelle nicht der Terminator sein ?

	return s;
}

void invariantenTests() {
	printf("\n\n *** Invarianten Tests *** \n\n");

	int i;
	for(i=0; i<20; i++) {
		char* s = rndString();
		char* r = reverse(s);
		char* n1 = normalisiere(s);
		char* n2 = normalisiere(r);
		char* n3 = reverse(n2);

		if(True == strCmp(n1,n3)) {
			printf("Okay %s", s);
		} else {
			printf("Fail %s", s);
		}

		free(s);
		free(r);
		free(n1);
		free(n2);
		free(n3);
	}



}


int main() {
	userTests();

	unitTests();

	invariantenTests();
}


