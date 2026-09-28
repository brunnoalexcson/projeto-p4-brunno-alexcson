using System.Collections.Generic;

namespace LabirintoPoo.Dominio;

// BFS: explora em camadas de distância, então o primeiro caminho que chega ao destino é mínimo
public class BuscaEmLargura
{
    private readonly Labirinto _labirinto;
    private readonly Posicao _origem;
    private readonly Posicao _destino;

    private Queue<Posicao> _fila;
    private Posicao[,] _anterior;

    // Motivos 4 a 7 da tabela 4.3 do README, nesta ordem
    public BuscaEmLargura(Labirinto labirinto, Posicao origem, Posicao destino)
    {
        if (!labirinto.DentroDosLimites(origem))
        {
            throw new EntradaInvalidaException("Origem fora dos limites");
        }
        if (!labirinto.DentroDosLimites(destino))
        {
            throw new EntradaInvalidaException("Destino fora dos limites");
        }
        if (!labirinto.CelulaLivre(origem))
        {
            throw new EntradaInvalidaException("Origem bloqueada");
        }
        if (!labirinto.CelulaLivre(destino))
        {
            throw new EntradaInvalidaException("Destino bloqueado");
        }

        _labirinto = labirinto;
        _origem = origem;
        _destino = destino;
    }

    // Devolve null quando não há caminho
    public Caminho BuscarCaminho()
    {
        _fila = new Queue<Posicao>();
        _anterior = new Posicao[_labirinto.TotalLinhas, _labirinto.TotalColunas];

        // A origem aponta para ela mesma
        Marcar(_origem, _origem);

        while (_fila.Count > 0)
        {
            Posicao atual = _fila.Dequeue();

            if (atual.MesmaPosicao(_destino))
            {
                return ReconstruirCaminho();
            }

            foreach (Posicao vizinha in _labirinto.Vizinhanca(atual))
            {
                // Célula marcada ao entrar na fila, para entrar uma única vez
                if (_anterior[vizinha.Linha, vizinha.Coluna] == null)
                {
                    Marcar(vizinha, atual);
                }
            }
        }
        return null;
    }

    private void Marcar(Posicao posicao, Posicao vindaDe)
    {
        _anterior[posicao.Linha, posicao.Coluna] = vindaDe;
        _fila.Enqueue(posicao);
    }

    // Volta do destino até a origem e depois inverte a lista
    private Caminho ReconstruirCaminho()
    {
        List<Posicao> posicoes = new List<Posicao>();
        Posicao atual = _destino;
        posicoes.Add(atual);
        while (!atual.MesmaPosicao(_origem))
        {
            atual = _anterior[atual.Linha, atual.Coluna];
            posicoes.Add(atual);
        }
        posicoes.Reverse();
        return new Caminho(posicoes);
    }
}