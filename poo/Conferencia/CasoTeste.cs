using System;
using LabirintoPoo.Dominio;

namespace LabirintoPoo.Conferencia;

public class CasoTeste
{
    private readonly string _id;
    private readonly string _titulo;
    private readonly string[] _linhas;
    private readonly Posicao _origem;
    private readonly Posicao _destino;
    private readonly string _saidaEsperada;

    public CasoTeste(string id, string titulo, string[] linhas, Posicao origem, Posicao destino, string saidaEsperada)
    {
        _id = id;
        _titulo = titulo;
        _linhas = linhas;
        _origem = origem;
        _destino = destino;
        _saidaEsperada = saidaEsperada;
    }

    public bool Executar()
    {
        Console.WriteLine("==================================================");
        Console.WriteLine(_id + " - " + _titulo);
        Console.WriteLine("--------------------------------------------------");
        Console.WriteLine("Entrada:");
        ImprimirEntrada();

        // Não precisa saber qual é o tipo de resultado: cada um escreve o próprio texto
        Resultado resultado = Solucionador.Resolver(_linhas, _origem, _destino);
        string saida = resultado.ToString();
        Console.WriteLine();
        Console.WriteLine("Saída obtida:");
        Console.WriteLine(saida);
        Console.WriteLine();

        // Conferência por texto exato com a saída esperada
        bool aprovado = saida == _saidaEsperada;
        if (aprovado)
        {
            Console.WriteLine("Conferência com testes/casos.md: OK");
        }
        else
        {
            Console.WriteLine("Conferência com testes/casos.md: FALHOU");
            Console.WriteLine("Saída esperada:");
            Console.WriteLine(_saidaEsperada);
        }
        Console.WriteLine();
        return aprovado;
    }

    // Usa os dados do caso, e não o Labirinto, porque um labirinto inválido nem chega a existir
    private void ImprimirEntrada()
    {
        string indices = "    ";
        if (_linhas.Length > 0)
        {
            for (int coluna = 0; coluna < _linhas[0].Length; coluna++)
            {
                indices = indices + (coluna % 10);
            }
        }
        Console.WriteLine(indices);

        for (int linha = 0; linha < _linhas.Length; linha++)
        {
            Console.WriteLine(linha.ToString().PadLeft(3) + " " + _linhas[linha]);
        }
        Console.WriteLine("Origem: " + _origem + "   Destino: " + _destino);
    }
}