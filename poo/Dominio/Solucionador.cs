namespace LabirintoPoo.Dominio;

public class Solucionador
{
    // Valida a entrada e, se for válida, busca o caminho
    public static Resultado Resolver(string[] linhas, Posicao origem, Posicao destino)
    {
        // Único ponto que transforma a exceção em resultado
        try
        {
            Labirinto labirinto = new Labirinto(linhas);
            BuscaEmLargura busca = new BuscaEmLargura(labirinto, origem, destino);
            Caminho caminho = busca.BuscarCaminho();
            if (caminho == null)
            {
                return new SemCaminho();
            }
            return new CaminhoEncontrado(caminho);
        }
        catch (EntradaInvalidaException erro)
        {
            return new EntradaInvalida(erro.Message);
        }
    }
}