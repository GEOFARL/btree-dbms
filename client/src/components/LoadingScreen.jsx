import { Bars } from 'react-loader-spinner';

const LoadingScreen = () => {
  return (
    <div className="loading-screen">
      <Bars
        height="80"
        width="80"
        color="#4fa94d"
        ariaLabel="bars-loading"
        wrapperStyle={{}}
        wrapperClass=""
        visible={true}
      />
    </div>
  );
};

export default LoadingScreen;
