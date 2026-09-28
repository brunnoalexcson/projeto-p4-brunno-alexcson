using System.Collections.Generic;

namespace LabirintoPoo.Dominio;

// O labirinto é estático: validado no construtor e nunca alterado
public class Labirinto
{
    private const char Livre = '.';
    private const char Bloqueada = '#';

    // Cada célula é só livre ou bloqueada, por isso não virou classe
    private readonly bool[,] _celulaLivre;

    public int TotalLinhas { get; private set; }
    public int TotalColunas { get; private set; }

    // A ordem segue a tabela 4.3 do README: um labirinto inválido nem chega a existir
    public Labirinto(string[] linhas)
    {
        if (LabirintoVazio(linhas))
        {
            throw new EntradaInvalidaException("Labirinto vazio");
        }
        if (!LinhasRegulares(linhas))
        {
            throw new EntradaInvalidaException("Linhas irregulares");
        }
        if (!CelulasConhecidas(linhas))
        {
            throw new EntradaInvalidaException("Célula desconhecida");
        }

        TotalLinhas = linhas.Length;
        TotalColunas = linhas[0].Length;
        _celulaLivre = new bool[TotalLinhas, TotalColunas];
        for (int linha = 0; linha < TotalLinhas; linha++)
        {
            for (int coluna = 0; coluna < TotalColunas; coluna++)
            {
                _celulaLivre[linha, coluna] = linhas[linha][coluna] == Livre;
            }
        }
    }

    public bool DentroDosLimites(Posicao posicao)
    {
        return posicao.Linha >= 0 && posicao.Linha < TotalLinhas
            && posicao.Coluna >= 0 && posicao.Coluna < TotalColunas;
    }

    // Testa os limites antes, para nunca acessar fora da matriz
    public bool CelulaLivre(Posicao posicao)
    {
        return DentroDosLimites(posicao) && _celulaLivre[posicao.Linha, posicao.Coluna];
    }

    public List<Posicao> Vizinhanca(Posicao posicao)
    {
        List<Posicao> vizinhanca = new List<Posicao>();
        foreach (Posicao vizinha in posicao.Vizinhas())
        {
            if (CelulaLivre(vizinha))
            {
                vizinhanca.Add(vizinha);
            }
        }
        return vizinhanca;
    }

    private bool LabirintoVazio(string[] linhas)
    {
        foreach (string linha in linhas)
        {
            if (linha.Length > 0)
            {
                return false;
            }
        }
        return true;
    }

    private bool LinhasRegulares(string[] linhas)
    {
        foreach (string linha in linhas)
        {
            if (linha.Length != linhas[0].Length)
            {
                return false;
            }
        }
        return true;
    }

    private bool CelulasConhecidas(string[] linhas)
    {
        foreach (string linha in linhas)
        {
            foreach (char celula in linha)
            {
                if (celula != Livre && celula != Bloqueada)
                {
                    return false;
                }
            }
        }
        return true;
    }
}