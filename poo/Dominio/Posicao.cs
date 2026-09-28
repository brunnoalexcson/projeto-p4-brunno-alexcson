using System.Collections.Generic;

namespace LabirintoPoo.Dominio;

// Uma célula do labirinto; não muda depois de criada (set privado)
public class Posicao
{
    public int Linha { get; private set; }
    public int Coluna { get; private set; }

    // Aceita qualquer valor: quem diz se a posição existe é o Labirinto
    public Posicao(int linha, int coluna)
    {
        Linha = linha;
        Coluna = coluna;
    }

    // A ordem cima, direita, baixo, esquerda é a ordem de exploração da BFS
    public List<Posicao> Vizinhas()
    {
        List<Posicao> vizinhas = new List<Posicao>();
        vizinhas.Add(new Posicao(Linha - 1, Coluna));
        vizinhas.Add(new Posicao(Linha, Coluna + 1));
        vizinhas.Add(new Posicao(Linha + 1, Coluna));
        vizinhas.Add(new Posicao(Linha, Coluna - 1));
        return vizinhas;
    }

    public bool MesmaPosicao(Posicao outra)
    {
        return Linha == outra.Linha && Coluna == outra.Coluna;
    }

    public override string ToString()
    {
        return "(" + Linha + "," + Coluna + ")";
    }
}