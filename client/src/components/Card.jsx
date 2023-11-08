// eslint-disable-next-line
const Card = ({ children, classNames }) => {
  return <div className={`card ${classNames}`}>{children}</div>;
};

export default Card;
