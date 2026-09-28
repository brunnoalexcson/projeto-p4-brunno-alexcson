using System;

namespace LabirintoPoo.Dominio;

public class EntradaInvalidaException : Exception
{
    public EntradaInvalidaException(string motivo) : base(motivo)
    {
    }
}