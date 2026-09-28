using System.Collections.Generic;

namespace LabirintoPoo.Dominio;

public class Caminho
{
    private readonly List<Posicao> _posicoes;

    public Caminho(List<Posicao> posicoes)
    {
        _posicoes = posicoes;
    }

    // Calculado a partir das posições, para nunca ficar inconsistente
    public int Movimentos()
    {
        return _posicoes.Count - 1;
    }

    public override string ToString()
    {
        return string.Join(" → ", _posicoes);
    }
}