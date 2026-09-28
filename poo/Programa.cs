// Projeto P4 - Caminho mínimo em labirinto - Implementação orientada a objetos [P4-ETAPA-04]
// Executa os 15 casos de testes/casos.md, declarados em Conferencia/CasosEtapa02.cs.

using System;
using System.Collections.Generic;
using System.Text;
using LabirintoPoo.Conferencia;

namespace LabirintoPoo;

public class Programa
{
    public static int Main()
    {
        Console.OutputEncoding = Encoding.UTF8;

        List<CasoTeste> casos = CasosEtapa02.Obter();

        int aprovados = 0;
        foreach (CasoTeste caso in casos)
        {
            if (caso.Executar())
            {
                aprovados = aprovados + 1;
            }
        }

        Console.WriteLine("==================================================");
        Console.WriteLine("Resumo: " + aprovados + " de " + casos.Count + " casos conferem com testes/casos.md");

        if (aprovados == casos.Count)
        {
            return 0;
        }
        return 1;
    }
}