#ifndef INGREDIENTES
#define INGREDIENTES

#define MAX_INGREDIENTES_POR_HAMBURGUER 10


namespace Geral {
    enum Ingredientes {
        VAZIO = 0,
        PAO_INFERIOR = 'x',
        PAO_SUPERIOR = 'z',
        CARNE = 'n',
        QUEIJO_SUICO = 's',
        QUEIJO_CHEDDAR = 'q',
        ALFACE = 'a',
        KETCHUP = 'k',
        MOSTARDA = 'm',
        PICLES = 'p',
        CEBOLA = 'c',
        TOMATE = 't',
        OVO = 'o',
        BACON = 'b',
};


    struct Hamburguer {
        int altura;
        Geral::Ingredientes pilha[MAX_INGREDIENTES_POR_HAMBURGUER];

        Hamburguer() {altura = 0;
            for (int i = 0; i < MAX_INGREDIENTES_POR_HAMBURGUER; i++) pilha[i] = Geral::Ingredientes::VAZIO;
        };

        int empilharIngrediente(Geral::Ingredientes ingrediente) {
            if (altura >= MAX_INGREDIENTES_POR_HAMBURGUER) return 1;
            pilha[altura] = ingrediente;
            altura++;

            return 0;
        }

        Geral::Ingredientes desempilharIngrediente() {
            if (altura <= 0) return Geral::Ingredientes::VAZIO;

            altura--;
            return pilha[altura];
        }
    };

}



#endif