using System.Collections.Generic;
using LabirintoPoo.Dominio;

namespace LabirintoPoo.Conferencia;

public class CasosEtapa02
{
    // Os 15 casos de testes/casos.md, na mesma ordem
    public static List<CasoTeste> Obter()
    {
        List<CasoTeste> casos = new List<CasoTeste>();

        casos.Add(new CasoTeste("CN-01", "Caminho mínimo único",
            new string[] { "..###", "#...#", "###.#", "....." },
            new Posicao(0, 0), new Posicao(3, 4),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0) → (0,1) → (1,1) → (1,2) → (1,3) → (2,3) → (3,3) → (3,4)\n" +
            "Movimentos: 7"));

        casos.Add(new CasoTeste("CN-02", "Vários caminhos mínimos",
            new string[] { "...", "...", "..." },
            new Posicao(0, 0), new Posicao(2, 2),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)\n" +
            "Movimentos: 4"));

        casos.Add(new CasoTeste("CN-03", "Desvio por uma única passagem",
            new string[] { "....", "##.#", "...." },
            new Posicao(0, 0), new Posicao(2, 0),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2) → (2,1) → (2,0)\n" +
            "Movimentos: 6"));

        casos.Add(new CasoTeste("CN-04", "Percurso no sentido inverso",
            new string[] { "..###", "#...#", "###.#", "....." },
            new Posicao(3, 4), new Posicao(0, 0),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (3,4) → (3,3) → (2,3) → (1,3) → (1,2) → (1,1) → (0,1) → (0,0)\n" +
            "Movimentos: 7"));

        casos.Add(new CasoTeste("CN-05", "Labirinto em serpentina",
            new string[] { ".....", "####.", ".....", ".####", "....." },
            new Posicao(0, 0), new Posicao(4, 4),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4) → (2,4) → (2,3)" +
            " → (2,2) → (2,1) → (2,0) → (3,0) → (4,0) → (4,1) → (4,2) → (4,3) → (4,4)\n" +
            "Movimentos: 16"));

        casos.Add(new CasoTeste("CN-06", "Escolha do menor entre dois percursos",
            new string[] { ".......", ".#####.", "......." },
            new Posicao(0, 1), new Posicao(2, 1),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,1) → (0,0) → (1,0) → (2,0) → (2,1)\n" +
            "Movimentos: 4"));

        casos.Add(new CasoTeste("CN-07", "Contorno de obstáculo",
            new string[] { ".....", "..#..", "....." },
            new Posicao(1, 0), new Posicao(1, 4),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (1,0) → (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4)\n" +
            "Movimentos: 6"));

        casos.Add(new CasoTeste("CN-08", "Labirinto com becos sem saída",
            new string[] { "..#.....", "#.#.###.", "#...#...", "###.#.##",
                           "#...#...", "#.###.#.", "#....##." },
            new Posicao(0, 0), new Posicao(6, 7),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0) → (0,1) → (1,1) → (2,1) → (2,2) → (2,3) → (1,3) → (0,3)" +
            " → (0,4) → (0,5) → (0,6) → (0,7) → (1,7) → (2,7) → (2,6) → (2,5)" +
            " → (3,5) → (4,5) → (4,6) → (4,7) → (5,7) → (6,7)\n" +
            "Movimentos: 21"));

        casos.Add(new CasoTeste("CN-09", "Destino inalcançável",
            new string[] { "..#", "###", "#.." },
            new Posicao(0, 0), new Posicao(2, 2),
            "Resultado: Sem caminho"));

        casos.Add(new CasoTeste("CN-10", "Destino cercado por paredes",
            new string[] { ".....", ".###.", ".#.#.", ".###.", "....." },
            new Posicao(0, 0), new Posicao(2, 2),
            "Resultado: Sem caminho"));

        casos.Add(new CasoTeste("CL-01", "Origem igual ao destino",
            new string[] { "...", "##.", "..." },
            new Posicao(0, 0), new Posicao(0, 0),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0)\n" +
            "Movimentos: 0"));

        casos.Add(new CasoTeste("CL-02", "Labirinto de uma única linha",
            new string[] { "....." },
            new Posicao(0, 0), new Posicao(0, 4),
            "Resultado: Caminho encontrado\n" +
            "Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4)\n" +
            "Movimentos: 4"));

        casos.Add(new CasoTeste("CL-03", "Ligação apenas pela diagonal",
            new string[] { ".#", "#." },
            new Posicao(0, 0), new Posicao(1, 1),
            "Resultado: Sem caminho"));

        casos.Add(new CasoTeste("CI-01", "Origem bloqueada",
            new string[] { "#.", ".." },
            new Posicao(0, 0), new Posicao(1, 1),
            "Resultado: Entrada inválida\n" +
            "Motivo: Origem bloqueada"));

        casos.Add(new CasoTeste("CI-02", "Destino fora dos limites",
            new string[] { "...", "..." },
            new Posicao(0, 0), new Posicao(2, 0),
            "Resultado: Entrada inválida\n" +
            "Motivo: Destino fora dos limites"));

        return casos;
    }
}