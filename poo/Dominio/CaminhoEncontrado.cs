namespace LabirintoPoo.Dominio;

// É um resultado que tem um caminho
public class CaminhoEncontrado : Resultado
{
    private readonly Caminho _caminho;

    public CaminhoEncontrado(Caminho caminho)
    {
        _caminho = caminho;
    }

    protected override string Descricao()
    {
        return "Caminho encontrado\nCaminho: " + _caminho + "\nMovimentos: " + _caminho.Movimentos();
    }
}