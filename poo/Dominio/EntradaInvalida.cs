namespace LabirintoPoo.Dominio;

public class EntradaInvalida : Resultado
{
    private readonly string _motivo;

    public EntradaInvalida(string motivo)
    {
        _motivo = motivo;
    }

    protected override string Descricao()
    {
        return "Entrada inválida\nMotivo: " + _motivo;
    }
}